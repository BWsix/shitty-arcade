#include "dbg.h"
#include "deque.h"
#include "game.h"
#include "raylib.h"
#include "snake.h"
#include <stdlib.h>

int main(void) {
  const int movesPerSecond = 9;
  const int boardWidth = 16;
  const int boardHeight = 16;
  const int cellWidth = 20;
  const int screenWidth = cellWidth * boardWidth;
  const int screenHeight = cellWidth * boardHeight;

  InitWindow(screenWidth, screenHeight, "Shitty Snake");

  // For `GetRandomValue` to get truly random
  Game *snakeGame =
      Game_create(boardWidth, boardHeight, cellWidth, movesPerSecond);

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
