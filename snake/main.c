#include "dbg.h"
#include "deque.h"
#include "game.h"
#include "snake.h"
#include <raylib.h>
#include <stdlib.h>

int main(void) {
  const int movesPerSecond = 9;
  const int boardWidth = 16;
  const int boardHeight = 16;
  const int cellWidth = 20;
  const int screenWidth = cellWidth * boardWidth;
  const int screenHeight = cellWidth * boardHeight;

  Game *snakeGame =
      Game_create(boardWidth, boardHeight, cellWidth, movesPerSecond);

  InitWindow(screenWidth, screenHeight, "Shitty Snake");
  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    Game_loop(snakeGame);

    BeginDrawing();
    Game_draw(snakeGame);
    EndDrawing();
  }
  CloseWindow();

  Game_destroy(snakeGame);

  return EXIT_SUCCESS;
}
