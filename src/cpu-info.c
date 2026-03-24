/*
 * cpu-info.c
 * Get information about CPU.
 * NOTE: Works only on GNU/Linux distributions.
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

/*
 * Get CPU architecture.
 * Argument 'buffer' is a pointer to a buffer that stores result,
 * and 'buffer_size' is the size (in bytes) of that buffer.
 * Stores CPU architecture or 'Unknown' if it cannot
 * be retrieved.
 */
void cpuArch(char *buffer, size_t buffer_size){
  struct utsname info;
  if (uname(&info) == 0){
    snprintf(buffer, buffer_size, "%s", info.machine);
  } else {
    snprintf(buffer, buffer_size, "Unknown");
  }
}

/*
 * Get CPU model name.
 * Argument 'buffer' is a pointer to a buffer that stores result,
 * and 'buffer_size' is the size (in bytes) of that buffer.
 * Stores CPU model name or error message if cannot read it.
 */
void cpuName(char *buffer, size_t buffer_size){
  FILE *fp = fopen("/proc/cpuinfo", "r");
  snprintf(buffer, buffer_size, "Unknown");
  
  if (!fp){
    snprintf(buffer, buffer_size, "Can't open /proc/cpuinfo. ");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), fp)){
    if (strstr(line, "model name")){
      char *ptr = strstr(line, ":");
      if (ptr){
	ptr++;
	while (*ptr == ' ' || *ptr == '\t'){
	  ptr++;
	}
	ptr[strcspn(ptr, "\r\n")] = '\0';
	snprintf(buffer, buffer_size, "%s", ptr);
	break;
      }
    }
  }
  fclose(fp);
}

/*
 * Get CPU number of threads (not cores).
 * Returns the number of CPU threads, -1 if it
 * cannot be retrieved.
 */
int cpuNproc(){
  int number = get_nprocs();
  if (number > 0){
    return number;
  } else {
    return -1;
  }
}

/*
 * Get CPU usage.
 * Returns average CPU usage (double) since last call in
 * percent (0% to 100%) or -1.0 if file cannot be opened.
 * NOTE: First call returns average CPU usage since system boot,
 * next call returns average since last call.
 */
double cpuUsage(){
  FILE *fp = fopen("/proc/stat", "r");
  long long user = 0, nice = 0, system = 0, idle = 0, iowait = 0, irq = 0, softirq = 0,
    steal = 0, curr_total = 0, curr_active = 0, delta_total = 0, delta_active = 0;
  static long long prev_total = 0, prev_active = 0;
  
  if (fp){
    fscanf(fp, " cpu %lld %lld %lld %lld %lld %lld %lld %lld", &user, &nice,
	   &system, &idle, &iowait, &irq, &softirq, &steal);
  } else {
    return -1.0;
  }
  fclose (fp);
  
  curr_total  = user + nice + system + idle + iowait + irq + softirq + steal;
  curr_active = user + nice + system + irq + softirq + steal;
  
  delta_total  = curr_total - prev_total;
  delta_active = curr_active - prev_active;
  
  prev_total  = curr_total;
  prev_active = curr_active;
  
  if (delta_total <= 0) return 0.0;
  return 100.0 * ((double)delta_active / (double)delta_total);
}
