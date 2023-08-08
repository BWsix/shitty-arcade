#include <raylib.h>
#include <stdbool.h>

#ifndef CELL_H
#define CELL_H

typedef struct Cell {
  bool isMine;
  bool revealed;
  bool marked;
  int surroundingMineCount;

  Rectangle rect;
} Cell;

typedef struct Game {
  int gapSize;
  int cellSize;
  int rowCount;
  int columnCount;
  Cell **cells;
  int mineCount;
  bool gameover;
  bool youWon;
} Game;

Game *Game_create(int gapSize, int cellSize, int rowCount, int columnCount);
void Game_destroy(Game *self);

void Game_loop(Game *self);
void Game_draw(Game *self);

#endif // !CELL_H
