/*
 * bar.c
 * Make a bar from input.
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#include <ncurses.h>
#include <stdlib.h>
#include <math.h>

/*
 * Draws a bar showing desired percentage information.
 * Arguments 'pos_y' and 'pos_x' are screen position, 'length'
 * is the bar length, and 'percent' is percentage of bar to fill (0-100).
 * Returns 0 on success, -1 if percent is out of range (0% to 100%).
 */
int makebar(int pos_y, int pos_x, int length, double percent){
  if (percent > 100 || percent < 0) return -1;
  int filled_bar = (int)round((percent / 100.0) * length);
  int i;
  
  mvprintw(pos_y, pos_x, "%5.1f%% ", percent);
  printw("[");
  for (i = 0; i < length; i++){
    if (i < filled_bar)
      addch ('#');
    else
      addch ('-');
  }

  printw ("]");
  return 0;
}
