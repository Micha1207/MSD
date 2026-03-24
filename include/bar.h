/*
 * bar.h
 * MSD - Micha1207's System Data program.
 *
 * Header file for src/bar.c
 *
 * Author:  Micha1207
 * Project: MSD (https://github.com/Micha1207/MSD)
 * Date:    Mar 24, 2026
 * License: GNU GPL v3 (full license in LICENSE file)
 * This program comes with NO WARRANTY; to the extent permitted by law.
 */
#ifndef BAR_H
#define BAR_H

#include <ncurses.h>
#include <stdlib.h>
#include <math.h>

int makebar(int pos_y, int pos_x, int length, double percent);

#endif
