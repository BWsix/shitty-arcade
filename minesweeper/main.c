#include "game.h"
#include "raylib.h"
#include <stdio.h>

int main(void) {
  const int gapSize = 5;
  const int cellSize = 30;
  const int rowCount = 10;
  const int columnCount = 10;
  const int screenWidth = (gapSize + cellSize) * columnCount + gapSize;
  const int screenHeight = (gapSize + cellSize) * rowCount + gapSize;

  InitWindow(screenWidth, screenHeight, "Shitty minesweeper");
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
