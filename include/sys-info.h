/*
 * sys-info.h
 * MSD - Micha1207's System Data program.
 *
 * Header file for src/sys-info.c
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

void osName(char *buffer, size_t buffer_size);
void osKernelName(char *buffer, size_t buffer_size);
int uptime();
int datetime(int *day, int *month, int *year, int *hour, int *min, int *sec);

#endif
