/*
 * sys-info.c
 * Get information about the system (hardware and software).
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

/*
 * Gets OS name.
 * Argument 'buffer' is a pointer to a buffer that stores result
 * and 'buffer_size' is the size of that buffer.
 * NOTE: Function is expecting /etc/os-release with '"', e.g.:
 *  PRETTY_NAME="Debian GNU/Linux 13 (trixie)"
 */
void osName(char *buffer, size_t buffer_size){ 
  FILE *fp = fopen("/etc/os-release", "r");
  
  if (!fp){
    snprintf(buffer, buffer_size, "Can't open '/etc/os-release'.");
    return;
  }
  
  char line[256];
  while (fgets(line, sizeof(line), fp)){
    if (strstr(line, "PRETTY_NAME")){
      char *ptr = strstr(line, "=");
      if (ptr){
	ptr += 2;
	char *end = strchr(ptr, '\n');
	if (end != NULL) end--;
	if (end) *end = '\0';
	snprintf(buffer, buffer_size, "%s", ptr);
	break;
      }
    }
  }
  
  fclose(fp);
}

/*
 * Get Kernel name.
 * Argument 'buffer' is a pointer to a buffer that stores Kernel name,
 * and 'buffer_size' is the size of that buffer.
 */
void osKernelName(char *buffer, size_t buffer_size){ 
  struct utsname info;
  if (uname(&info) == 0){
    snprintf(buffer, buffer_size, "%s", info.release);
  } else {
    snprintf(buffer, buffer_size, "Unknown");
    return;
  }
}

/*
 * Get System uptime.
 * Returns system uptime in seconds, -1 if file cannot be opened,
 * -2 if cannot read it.
 */
int uptime(){
  FILE *fp = fopen("/proc/uptime", "r");
  double uptime_seconds = -1;
  int status = 0;
  if (!fp) return -1;

  status = fscanf(fp, "%lf", &uptime_seconds);
  fclose(fp);
  
  if (status <= 0) return -2;

  return (int)uptime_seconds;
}
/*
 * Gets date and time.
 * Arguments are integer pointers to variables, that store information.
 * Returns 0 on success.
 */
int datetime(int *day, int *month, int *year, int *hour, int *min, int *sec){
  time_t t = time(NULL);
  struct tm *now = localtime(&t);
  
  *day   = now->tm_mday;
  *month = now->tm_mon  + 1;
  *year  = now->tm_year + 1900;
  *hour  = now->tm_hour;
  *min   = now->tm_min;
  *sec   = now->tm_sec;

  return 0;
}
