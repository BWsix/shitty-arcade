#include "ai.h"

int lines[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
    {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6},
};

bool Wins(Cell cells[9], Cell who) {
  for (int i = 0; i < 8; i++) {
    Cell cell1 = cells[lines[i][0]];
    Cell cell2 = cells[lines[i][1]];
    Cell cell3 = cells[lines[i][2]];
    if (cell1 == who && cell2 == who && cell3 == who) {
      return true;
    }
  }
  return false;
}

bool IsBoardFull(Cell cells[9]) {
  for (int i = 0; i < 9; i++) {
    if (cells[i] == Empty) {
      return false;
    }
  }
  return true;
}

void PlaceNextMove(Cell cells[9]) {
  for (int i = 0; i < 9; i++) {
    if (cells[i] != Empty) {
      continue;
    }

    // if ai can win in one move, `attach`
    cells[i] = AI;
    if (Wins(cells, AI)) {
      return;
    }
    cells[i] = Empty;

    // if player can win in one move, `defend`
    cells[i] = Player;
    if (Wins(cells, Player)) {
      cells[i] = AI;
      return;
    }
    cells[i] = Empty;
  }

  // if center is empty, `place at center`
  if (cells[4] == Empty) {
    cells[4] = AI;
    return;
  }

  // else `place at first empty cell`
  for (int i = 0; i < 9; i++) {
    if (cells[i] != Empty) {
      continue;
    }

    cells[i] = AI;
    return;
  }
}
