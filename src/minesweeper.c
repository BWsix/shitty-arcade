#include <stdbool.h>
#include <stdlib.h>

#define BUTTON_IMPLEMENTATION
#include "button.h"
#include "dbg.h"
#define DEQUE_IMPLEMENTATION
#include "deque.h"
#include "raylib.h"

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

int dirs[8][2] = {
    {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1},
};

Game *Game_create(int gapSize, int cellSize, int rowCount, int columnCount) {
  Game *self = calloc(1, sizeof(Game));
  self->gapSize = gapSize;
  self->cellSize = cellSize;
  self->rowCount = rowCount;
  self->columnCount = columnCount;
  self->cells = calloc(rowCount, sizeof(Cell *));
  self->mineCount = 0;
  self->gameover = false;
  self->youWon = false;

  for (int r = 0; r < rowCount; r++) {
    self->cells[r] = calloc(columnCount, sizeof(Cell));
    for (int c = 0; c < columnCount; c++) {
      bool isMine = GetRandomValue(0, 1000) <= 100;
      self->mineCount += isMine;
      Cell cell;
      cell.isMine = isMine;
      cell.marked = false;
      cell.revealed = false;
      cell.surroundingMineCount = 0;
      cell.rect = (Rectangle){
          .x = (gapSize + cellSize) * c + gapSize,
          .y = (gapSize + cellSize) * r + gapSize,
          .width = cellSize,
          .height = cellSize,
      };
      self->cells[r][c] = cell;
    }
  }

  for (int r = 0; r < rowCount; r++) {
    for (int c = 0; c < columnCount; c++) {
      for (int i = 0; i < 8; i++) {
        int R = r + dirs[i][0];
        int C = c + dirs[i][1];
        if (R < 0 || R >= rowCount || C < 0 || C >= columnCount) {
          continue;
        }
        if (self->cells[R][C].isMine) {
          self->cells[r][c].surroundingMineCount += 1;
        }
      }
    }
  }

  return self;
}

void Game_destroy(Game *self) {
  for (int i = 0; i < self->rowCount; i++) {
    free(self->cells[i]);
  }
  free(self->cells);
  free(self);
}

typedef struct Point {
  int r;
  int c;
} Point;

void Game_reveal(Game *self, int r, int c) {
  self->cells[r][c].revealed = true;
  if (self->cells[r][c].surroundingMineCount != 0) {
    return;
  }

  Deque *queue = Deque_create();
  Point *point = malloc(sizeof(Point));
  point->r = r;
  point->c = c;
  Deque_pushback(queue, point);

  while (Deque_size(queue)) {
    Point point = *(Point *)Deque_front(queue);
    free(Deque_popfront(queue));

    // all 8 cell are guaranteed *not* to be mine
    for (int i = 0; i < 8; i++) {
      int R = point.r + dirs[i][0];
      int C = point.c + dirs[i][1];

      if (R < 0 || R >= self->rowCount || C < 0 || C >= self->columnCount) {
        continue;
      }
      if (self->cells[R][C].revealed) {
        continue;
      }

      self->cells[R][C].revealed = true;
      if (self->cells[R][C].surroundingMineCount == 0) {
        Point *point = malloc(sizeof(Point));
        point->r = R;
        point->c = C;
        Deque_pushback(queue, point);
      }
    }
  }

  Deque_destroy(queue);
}

void Game_loop(Game *self) {
  if (self->gameover) {
    return;
  }

  int mineLeft = self->mineCount;

  for (int r = 0; r < self->rowCount; r++) {
    for (int c = 0; c < self->columnCount; c++) {
      Cell cell = self->cells[r][c];
      if (cell.revealed) {
        continue;
      }

      if (GetButtonState(cell.rect, MOUSE_BUTTON_RIGHT) == BUTTON_ACTIVATED) {
        cell.marked = !cell.marked;
        self->cells[r][c].marked = cell.marked;
      }

      if (cell.marked) {
        mineLeft -= cell.isMine;
        continue;
      }

      if (GetButtonState(cell.rect, MOUSE_BUTTON_LEFT) == BUTTON_ACTIVATED) {
        if (cell.isMine) {
          self->gameover = true;
        } else {
          Game_reveal(self, r, c);
        }
      }
    }
  }

  if (!mineLeft) {
    self->youWon = true;
    self->gameover = true;
  }
}

void Game_draw(Game *self) {
  ClearBackground(DARKGRAY);

  for (int r = 0; r < self->rowCount; r++) {
    for (int c = 0; c < self->columnCount; c++) {
      Cell cell = self->cells[r][c];
      ButtonState state = GetButtonState(cell.rect, MOUSE_BUTTON_LEFT);

      Color color = LIGHTGRAY;
      if (!self->gameover && state == BUTTON_HOVERED && !cell.revealed) {
        color = WHITE;
      } else if (cell.revealed) {
        color = RAYWHITE;
      }

      DrawRectangleRec(cell.rect, color);

      char message[] = " ";
      if (cell.marked) {
        message[0] = 'X';
      } else if (cell.revealed) {
        if (cell.surroundingMineCount) {
          message[0] = '0' + cell.surroundingMineCount;
        }
      }
      DrawText(message, cell.rect.x + 5, cell.rect.y, self->cellSize, BLACK);
    }
  }

  if (self->gameover) {
    char *message = self->youWon ? "YOU WON" : "YOU DIED";
    DrawText(message, 10, 10, 65, RED);
  }
}

int main(void) {
  const int gapSize = 5;
  const int cellSize = 30;
  const int rowCount = 10;
  const int columnCount = 10;
  const int screenWidth = (gapSize + cellSize) * columnCount + gapSize;
  const int screenHeight = (gapSize + cellSize) * rowCount + gapSize;

  InitWindow(screenWidth, screenHeight, "Shitty Minesweeper");
  Game *game = Game_create(gapSize, cellSize, rowCount, columnCount);

  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    Game_loop(game);

    BeginDrawing();
    Game_draw(game);
    EndDrawing();
  }

  CloseWindow();
  Game_destroy(game);

  return 0;
}
