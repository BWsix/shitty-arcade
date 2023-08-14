#include "button.h"
#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef int Board[9][9];
#define BOARD_AT(board, r, c) (board)[(r)][(c)]

void shuffle(int arr[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void Board_fill(Board board, int n) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      BOARD_AT(board, r, c) = n;
    }
  }
}

void Board_print(Board board) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (c < 8 && c % 3 == 2) {
        printf("%d | ", BOARD_AT(board, r, c));
      } else {
        printf("%d ", BOARD_AT(board, r, c));
      }
    }
    if (r < 8 && r % 3 == 2) {
      printf("\n---------------------\n");
    } else {
      printf("\n");
    }
  }
}

bool row_contains(Board board, int r, int n) {
  for (int c = 0; c < 9; c++) {
    if (BOARD_AT(board, r, c) == n)
      return true;
  }
  return false;
}

bool col_contains(Board board, int c, int n) {
  for (int r = 0; r < 9; r++) {
    if (BOARD_AT(board, r, c) == n)
      return true;
  }
  return false;
}

bool grid_contains(Board board, int i, int j, int n) {
  for (int R = 0; R < 3; R++) {
    for (int C = 0; C < 3; C++) {
      int r = R + i * 3;
      int c = C + j * 3;
      if (BOARD_AT(board, r, c) == n)
        return true;
    }
  }
  return false;
}

bool Board_check(Board board) {
  for (int r = 0; r < 9; r++) {
    int check = 0;
    int target = 0;
    for (int c = 0; c < 9; c++) {
      check |= 1 << BOARD_AT(board, r, c);
      target |= 1 << (c + 1);
    }
    if (check != target) {
      return false;
    }
  }

  for (int c = 0; c < 9; c++) {
    int check = 0;
    int target = 0;
    for (int r = 0; r < 9; r++) {
      check |= 1 << BOARD_AT(board, c, r);
      target |= 1 << (r + 1);
    }
    if (check != target) {
      return false;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int check = 0;
      int target = 0;
      for (int k = 0; k < 9; k++) {
        target |= 1 << (k + 1);
      }
      for (int R = 0; R < 3; R++) {
        for (int C = 0; C < 3; C++) {
          int r = R + i * 3;
          int c = C + j * 3;
          check |= 1 << BOARD_AT(board, r, c);
        }
      }
      if (check != target) {
        return false;
      }
    }
  }

  return true;
}

bool Board_rand(Board board, int idx) {
  if (idx == 9 * 9) {
    return Board_check(board);
  }

  int r = idx / 9;
  int c = idx % 9;

  if (BOARD_AT(board, r, c)) {
    return Board_rand(board, idx + 1);
  }

  int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  srand(time(NULL) + idx);
  shuffle(nums, 9);

  for (int i = 0; i < 9; i++) {
    int num = nums[i];
    if (row_contains(board, r, num) || col_contains(board, c, num) ||
        grid_contains(board, r / 3, c / 3, num)) {
      continue;
    }
    BOARD_AT(board, r, c) = num;
    if (Board_rand(board, idx + 1)) {
      return true;
    }
  }
  BOARD_AT(board, r, c) = 0;
  return false;
}

void Board_copy(Board dst, const Board board) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      BOARD_AT(dst, r, c) = BOARD_AT(board, r, c);
    }
  }
}

void Board_remove(Board board, int n) {
  int nums[81];
  for (int i = 0; i < 81; i++) {
    nums[i] = i;
  }
  srand(time(NULL));
  shuffle(nums, 81);

  for (int i = 0; i < n; i++) {
    int r = nums[i] / 9;
    int c = nums[i] % 9;
    BOARD_AT(board, r, c) = 0;
  }
}

int main(void) {
  Board board, userInput;
  Board_fill(board, 0);
  Board_rand(board, 0);
  assert(Board_check(board));
  Board_remove(board, 27);
  Board_copy(userInput, board);

  ////////////////////////////////////////////////////////////////////////

  const int gapSize = 5;
  const int cellSize = 50;
  const int rowCount = 9;
  const int columnCount = 9;
  const int screenWidth = (gapSize + cellSize) * columnCount + gapSize;
  const int screenHeight = (gapSize + cellSize) * rowCount + gapSize;
  InitWindow(screenWidth, screenHeight, "Shitty sudoku");

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
