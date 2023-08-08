#include "raylib.h"

#ifndef GAME_H
#define GAME_H

typedef enum Cell {
  Empty = ' ',
  Player = 'O',
  AI = 'X',
} Cell;

bool Wins(Cell cells[9], Cell who);
bool IsBoardFull(Cell cells[9]);
void PlaceNextMove(Cell cells[9]);

#endif // !GAME_H
