#include "game_of_life.h"

int main() {
  int **old_arr = allocate(), **new_arr = allocate();
  input_start(old_arr);
  if (freopen("/dev/tty", "r", stdin)) {
    initscr();
    nodelay(stdscr, 1);
    int exit = 0, speed = 15000, speed_factor = 5;
    while (!exit) {
      char key;
      clear();
      usleep(speed);
      mk_new_arr(old_arr, new_arr);
      update(old_arr, new_arr);
      key = getch();
      press_key(key, &exit, &speed, &speed_factor);
      draw(old_arr);
      printw(
          "%36cSpeed = %d%27cExit - 'q'\n%36cIncrease - '+'\n%36cDecrease - "
          "'-'",
          ' ', speed_factor, ' ', ' ', ' ');
      refresh();
    }
    endwin();
    free_arr(old_arr);
    free_arr(new_arr);
  }
  return 0;
}

int **allocate() {
  int **arr;
  arr = (int **)malloc((HEIGHT + 2) * sizeof(int *));
  for (int i = 0; i < HEIGHT + 2; i++) {
    arr[i] = (int *)malloc((WIDTH + 2) * sizeof(int));
  }
  return arr;
}

void free_arr(int **arr) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    free(arr[i]);
  }
  free(arr);
}

void press_key(char key, int *exit, int *speed, int *speed_factor) {
  switch (key) {
    case 'q':
      *exit = 1;
      break;
    case '=':
      if (*speed_factor != 9) {
        *speed -= 3000;
        *speed_factor += 1;
      }
      break;
    case '-':
      if (*speed_factor != 0) {
        *speed += 3000;
        *speed_factor -= 1;
      }
      break;
    default:
      break;
  }
}

void input_start(int **old_arr) {
  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int j = 1; j < WIDTH + 1; j++) {
      scanf("%d", &old_arr[i][j]);
    }
  }
}

void draw(int **old_arr) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      if (i == 0 || i == 26 || j == 0 || j == 81) {
        printw("x");
      } else if (old_arr[i][j] == 0) {
        printw(" ");
      } else if (old_arr[i][j] == 1) {
        printw("*");
      }
    }
    printw("\n");
  }
}

void mk_new_arr(int **old_arr, int **new_arr) {
  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int j = 1; j < WIDTH + 1; j++) {
      int neigh = count_neigh(old_arr, i, j);
      if (old_arr[i][j] == 0 && neigh == 3) {
        new_arr[i][j] = 1;
      } else if (old_arr[i][j] == 1 && (neigh == 2 || neigh == 3)) {
        new_arr[i][j] = 1;
      } else {
        new_arr[i][j] = 0;
      }
    }
  }
}

int count_neigh(int **old_arr, int i, int j) {
  int i_upper = i - 1, i_bottom = i + 1, j_right = j + 1, j_left = j - 1;
  if (i == 1) {
    i_upper = HEIGHT;
  }
  if (i == HEIGHT) {
    i_bottom = 1;
  }
  if (j == 1) {
    j_left = WIDTH;
  }
  if (j == WIDTH) {
    j_right = 1;
  }
  int res = old_arr[i_upper][j_left] + old_arr[i_upper][j] +
            old_arr[i_upper][j_right] + old_arr[i][j_left] +
            old_arr[i][j_right] + old_arr[i_bottom][j_left] +
            old_arr[i_bottom][j] + old_arr[i_bottom][j_right];
  return res;
}

void update(int **old_arr, int **new_arr) {
  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int j = 1; j < WIDTH + 1; j++) {
      old_arr[i][j] = new_arr[i][j];
      new_arr[i][j] = 0;
    }
  }
}
