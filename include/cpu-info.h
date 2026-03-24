/*
 * cpu-info.h
 * MSD - Micha1207's System Data program.
 *
 * Header file for src/cpu-info.c
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

void cpuArch(char *buffer, size_t buffer_size);
void cpuName(char *buffer, size_t buffer_size);
int cpuNproc();
double cpuUsage();

#endif
