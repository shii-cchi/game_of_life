#ifndef SRC_GAME_OF_LIFE_H_
#define SRC_GAME_OF_LIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncurses.h"

#define WIDTH 80
#define HEIGHT 25

int **allocate();
void free_arr(int **arr);
void press_key(char key, int *exit, int *speed, int *speed_factor);
void input_start(int **old_arr);
void draw(int **old_arr);
void mk_new_arr(int **old_arr, int **new_arr);
int count_neigh(int **old_arr, int i, int j);
void update(int **old_arr, int **new_arr);

#endif  // SRC_GAME_OF_LIFE_H_
