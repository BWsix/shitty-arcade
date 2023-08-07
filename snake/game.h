#include "snake.h"

#ifndef GAME_H
#define GAME_H

typedef struct Game {
  int board_width;
  int board_height;
  int cell_width;
  Deque *walls;

  Snake *snake;
  Direction next_heading;
  int moves_per_second;

  Vector2 apple;
  float time_counter;
  bool gameover;
} Game;

Game *Game_create(int board_width, int board_height, int cell_width,
                  int moves_per_second);
void Game_destroy(Game *self);

Vector2 Game_get_random_cell(Game *self);

void Game_loop(Game *self);
void Game_draw(Game *self);

#endif // !GAME_H
