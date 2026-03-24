/*
 * main.c
 * MSD - Micha1207's System Data program.
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>

#include "cpu-info.h"
#include "ram-info.h"
#include "sys-info.h"
#include "bar.h"

/*
 * Main function.
 * Initialise NCurses and display system information (with
 * colors) in a loop.
 * Retrieve static information (e.g. CPU name) and dynamic
 * information (e.g. CPU usage).
 * Exit by pressing q or Q.
 * Returns 0 on success.
 */
int main(){
  int ch, cpu_nproc = -1, term_y = 0, term_x = 0, day = 0, month = 0,
    year = 0, hour = 0, min = 0, sec = 0, uptime_val = 0, uptime_sec = 0,
    uptime_min = 0, uptime_hrs = 0;
  char cpu_name[128], cpu_arch[16], os_name[32], hostname[256],
    *username = getenv("USER"), os_kernel_name[64];
  double ram_avail, ram_total, ram_usage, ram_percent = 0.0,
    cpu_usage = 0.0;
  
  initscr();
  raw();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  clear();
  timeout(1000);
  
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  
  cpuName(cpu_name, 128);
  cpu_nproc = cpuNproc();
  cpuArch(cpu_arch, 16);
  osName(os_name, 32);
  osKernelName(os_kernel_name, 64);
  gethostname(hostname, sizeof(hostname));
  cpuUsage();
  if (!username) username = "user";
  
  while (1){
    ch = getch();
    if (ch == 'q' || ch == 'Q') break;
    getmaxyx(stdscr, term_y, term_x);
    cpu_usage = cpuUsage();
    
    ramInfo(&ram_avail, &ram_total);
    ram_usage = ram_total - ram_avail;
    ram_percent = 100.0 * (ram_usage / ram_total);
    
    uptime_val = uptime();
    uptime_hrs = uptime_val / 3600;
    uptime_min = (uptime_val % 3600) / 60;
    uptime_sec = uptime_val % 60;
    
    datetime(&day, &month, &year, &hour, &min, &sec);
    
    erase();
    
    attron(COLOR_PAIR(3));
    mvprintw(0, 10, " ====== MSD ====== ");
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, 0, "%s@%s", username, hostname);
    mvprintw(3, 0, "OS:");
    mvprintw(4, 0, "Kernel:");
    mvprintw(5, 0, "Uptime:");
    mvprintw(6, 0, "Time:");
    mvprintw(8, 0, "CPU:");
    mvprintw(11, 0, "RAM:");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    attron(COLOR_PAIR(2));
    mvprintw(3, 8, "%s", os_name);
    mvprintw(4, 8, "%s", os_kernel_name);
    mvprintw(5, 8, "%dh, %dmin, %dsec", uptime_hrs, uptime_min, uptime_sec);
    mvprintw(6, 8, "%d.%02d.%04d, %d:%02d:%02d", day, month, year, hour, min, sec);
    mvprintw(8, 8, "%s (%d threads, %s)", cpu_name, cpu_nproc, cpu_arch);
    makebar(9, 2, floor(term_x / 3), cpu_usage);
    mvprintw(11, 8, "%.2f GiB used, %.2f GiB total", ram_usage, ram_total);
    makebar(12, 2, floor(term_x / 3), ram_percent);
    mvprintw(term_y - 1, 0, "Press q or Q to quit.");
    attroff(COLOR_PAIR(2));
    
    refresh();
  }
  
  endwin();
  return 0;
}
