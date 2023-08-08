#include <stdio.h>
#include <stdlib.h>

#include "ai.h"
#include "button.h"
#include "dbg.h"
#include "deque.h"
#include "raylib.h"

int main(void) {
  const int buttonWidth = 180;
  const int gapWidth = 20;
  const int boardWidth = 3;
  const int boardHeight = 3;
  const int screenWidth = (gapWidth + buttonWidth) * boardWidth + gapWidth;
  const int screenHeight = (gapWidth + buttonWidth) * boardHeight + gapWidth;

  Cell winner = Empty;
  bool gameover = false;
  Rectangle buttons[9];
  Cell cells[9];

  for (size_t r = 0; r < boardHeight; r++) {
    for (size_t c = 0; c < boardWidth; c++) {
      Rectangle button = {.x = buttonWidth * c + gapWidth * (c + 1),
                          .y = buttonWidth * r + gapWidth * (r + 1),
                          .width = buttonWidth,
                          .height = buttonWidth};
      buttons[r * boardWidth + c] = button;
      cells[r * boardWidth + c] = Empty;
    };
  };

  InitWindow(screenWidth, screenHeight, "Shitty Tic-Tac-Toe");

  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    for (int i = 0; i < 9; i++) {
      ButtonState state = GetButtonState(buttons[i]);

      if (state == BUTTON_ACTIVATED && cells[i] == Empty) {
        cells[i] = Player;

        if (Wins(cells, Player)) {
          winner = Player;
          gameover = true;
        } else if (IsBoardFull(cells)) {
          gameover = true;
        } else {
          PlaceNextMove(cells);
          if (Wins(cells, AI)) {
            winner = AI;
            gameover = true;
          }
        }
      }
    }

    BeginDrawing();
    ClearBackground(GetColor(0x101010ff));

    for (int i = 0; i < 9; i++) {
      Rectangle button = buttons[i];
      ButtonState state = GetButtonState(button);
      Cell cell = cells[i];

      if (state == BUTTON_HOVERED && cell == Empty && !gameover) {
        DrawRectangleRec(button, GetColor(0x505050ff));
      } else {
        DrawRectangleRec(button, GetColor(0x303030ff));
      }

      char message[] = " ";
      message[0] = cell;
      DrawText(message, button.x + 35, button.y + 10, button.height, RAYWHITE);
    }

    if (gameover) {
      char *message;
      switch (winner) {
      case Player:
        message = "YOU WON";
        break;
      case AI:
        message = "YOU DIED";
        break;
      case Empty:
        message = "TIE";
        break;
      }

      DrawText(message, 40, 40, 100, RED);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
