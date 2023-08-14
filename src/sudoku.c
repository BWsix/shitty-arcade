#include <assert.h>

#define BUTTON_IMPLEMENTATION
#include "button.h"
#include "raylib.h"
#define SUDOKU_IMPLEMENTATION
#include "sudoku.h"

int main(void) {
  Board board, userInput;
  Board_fill(board, 0);
  Board_rand(board, 0);
  assert(Board_check(board));
  Board_remove(board, 27);
  Board_copy(userInput, board);

  const int gapSize = 5;
  const int cellSize = 50;
  const int rowCount = 9;
  const int columnCount = 9;
  const int screenWidth = (gapSize + cellSize) * columnCount + gapSize;
  const int screenHeight = (gapSize + cellSize) * rowCount + gapSize;
  InitWindow(screenWidth, screenHeight, "Shitty Sudoku");

  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x202020ff));

    for (size_t r = 0; r < 9; r++) {
      for (size_t c = 0; c < 9; c++) {
        Rectangle box = {
            .x = (gapSize + cellSize) * c + gapSize,
            .y = (gapSize + cellSize) * r + gapSize,
            .width = cellSize,
            .height = cellSize,
        };

        char buf[256];
        DrawRectangleRec(box, RAYWHITE);
        if (BOARD_AT(board, r, c) == 0) {
          if (GetButtonState(box, MOUSE_BUTTON_LEFT) == BUTTON_HOVERED) {
            DrawRectangleRec(box, LIGHTGRAY);
            int num = GetCharPressed() - '0';
            if (1 <= num && num <= 9) {
              BOARD_AT(userInput, r, c) = num;
            }
          }
        }

        if (BOARD_AT(board, r, c)) {
          snprintf(buf, sizeof(buf), "%d", BOARD_AT(board, r, c));
          DrawText(buf, box.x + 15, box.y, cellSize, BLACK);
        } else if (BOARD_AT(userInput, r, c)) {
          snprintf(buf, sizeof(buf), "%d", BOARD_AT(userInput, r, c));
          DrawText(buf, box.x + 15, box.y, cellSize, BLUE);
        }
      }
    }

    DrawRectangle(3 * (cellSize + gapSize), gapSize, gapSize,
                  screenHeight - 2 * gapSize, GREEN);
    DrawRectangle(6 * (cellSize + gapSize), gapSize, gapSize,
                  screenHeight - 2 * gapSize, GREEN);
    DrawRectangle(gapSize, 3 * (cellSize + gapSize), screenHeight - 2 * gapSize,
                  gapSize, GREEN);
    DrawRectangle(gapSize, 6 * (cellSize + gapSize), screenHeight - 2 * gapSize,
                  gapSize, GREEN);

    if (Board_check(userInput)) {
      DrawText("YOU WON", 30, 30, 100, RED);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
