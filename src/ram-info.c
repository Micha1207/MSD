/*
 * ram-info.c
 * Get RAM memory usage and its total capacity.
 * NOTE: Works only on GNU/Linux distributions.
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#include <stdio.h>

/*
 * Gets information about RAM memory.
 * Arguments 'avail' and 'total' are pointers to variables (doubles), where
 * information about size of available and total memory are stored (in GiB).
 * Returns 0 on success, or -1 if file cannot be opened.
 */
int ramInfo(double *avail, double *total){
  FILE *fp = fopen("/proc/meminfo", "r");
  char line[256];
  long avail_kB = 0, total_kB = 0;
  int found = 0;
  
  if (fp == NULL) return -1;
  
  while (fgets(line, sizeof(line), fp)){
    if (sscanf(line, "MemTotal: %ld kB", &total_kB) == 1) found++;
    if (sscanf(line, "MemAvailable: %ld kB", &avail_kB) == 1) found++;

    if (found == 2) break;
  }
  fclose(fp);

  if (found != 2) return -1;
  
  *avail = avail_kB / (1024.0 * 1024.0);
  *total = total_kB / (1024.0 * 1024.0);
  
  return 0;
}
