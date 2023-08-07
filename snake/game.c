#include "game.h"
#include "dbg.h"
#include "deque.h"
#include <raylib.h>
#include <stdlib.h>

Deque *Wall_get(int width, int height) {
  Deque *walls = Deque_create();

  for (int y = 0; y < height; y++) {
    Vector2 *left = malloc(sizeof(Vector2));
    left->x = 0;
    left->y = y;
    Deque_pushback(walls, left);

    Vector2 *right = malloc(sizeof(Vector2));
    right->x = width - 1;
    right->y = y;
    Deque_pushback(walls, right);
  }
  for (int x = 0; x < width; x++) {
    Vector2 *top = malloc(sizeof(Vector2));
    top->x = x;
    top->y = 0;
    Deque_pushback(walls, top);

    Vector2 *bottom = malloc(sizeof(Vector2));
    bottom->x = x;
    bottom->y = height - 1;
    Deque_pushback(walls, bottom);
  }

  return walls;
}

bool Wall_contains(Deque *walls, Vector2 cell) {
  for (int i = 0; i < Deque_size(walls); i++) {
    Vector2 *wall = (Vector2 *)Deque_at(walls, i);
    if (wall->x == cell.x && wall->y == cell.y) {
      return true;
    }
  }
  return false;
}

Game *Game_create(int board_width, int board_height, int cell_width,
                  int moves_per_second) {
  Game *self = malloc(sizeof(Game));

  self->board_width = board_width;
  self->board_height = board_height;
  self->cell_width = cell_width;
  self->walls = Wall_get(board_width, board_height);

  self->snake = Snake_create();
  self->next_heading = East;
  self->moves_per_second = moves_per_second;

  self->apple = Game_get_random_cell(self);
  self->time_counter = 0.0f;
  self->gameover = false;

  return self;
}

void Game_destroy(Game *self) {
  for (int i = 0; i < Deque_size(self->walls); i++) {
    free(Deque_at(self->walls, i));
  }
  Deque_destroy(self->walls);
  Snake_destroy(self->snake);
  free(self);
}

Vector2 Game_get_random_cell(Game *self) {
  while (true) {
    Vector2 cell = {.x = GetRandomValue(1, self->board_width - 1),
                    .y = GetRandomValue(1, self->board_height - 1)};

    if (Wall_contains(self->walls, cell)) {
      continue;
    }
    if (Snake_contains(self->snake, cell)) {
      continue;
    }

    Vector2 next_cell = Snake_get_next_cell(self->snake);
    if (next_cell.x == cell.x || next_cell.y == cell.y) {
      continue;
    }

    return cell;
  }
}

void Game_loop(Game *self) {
  self->time_counter += GetFrameTime();

  if (IsKeyPressed(KEY_W)) {
    self->next_heading = North;
  }
  if (IsKeyPressed(KEY_D)) {
    self->next_heading = East;
  }
  if (IsKeyPressed(KEY_S)) {
    self->next_heading = South;
  }
  if (IsKeyPressed(KEY_A)) {
    self->next_heading = West;
  }

  if (self->time_counter > (1.0f / self->moves_per_second)) {
    self->time_counter = 0.0f;
    Snake_change_heading(self->snake, self->next_heading);
    Vector2 next_cell = Snake_get_next_cell(self->snake);

    if (Snake_contains(self->snake, next_cell)) {
      self->gameover = true;
    }
    if (Wall_contains(self->walls, next_cell)) {
      self->gameover = true;
    }
    if (self->gameover) {
      return;
    }

    if (next_cell.x == self->apple.x && next_cell.y == self->apple.y) {
      Snake_grow(self->snake, next_cell);

      Vector2 *new_wall = malloc(sizeof(Vector2));
      *new_wall = Game_get_random_cell(self);
      Deque_pushback(self->walls, new_wall);

      self->apple = Game_get_random_cell(self);
    } else {
      Snake_move(self->snake, next_cell);
    }
  }
}

Vector2 Game_project_cell_to_screen(Game *self, Vector2 cell) {
  return (Vector2){.x = cell.x * self->cell_width,
                   .y = cell.y * self->cell_width};
}

void Game_draw(Game *self) {
  Vector2 cell = {.x = self->cell_width, .y = self->cell_width};

  ClearBackground(RAYWHITE);

  for (int i = 0; i < Deque_size(self->snake->body); i++) {
    Vector2 top_left = Game_project_cell_to_screen(
        self, *(Vector2 *)Deque_at(self->snake->body, i));
    DrawRectangleV(top_left, cell, BLACK);
  }

  for (int i = 0; i < Deque_size(self->walls); i++) {
    Vector2 top_left =
        Game_project_cell_to_screen(self, *(Vector2 *)Deque_at(self->walls, i));
    DrawRectangleV(top_left, cell, ORANGE);
  }

  DrawRectangleV(Game_project_cell_to_screen(self, self->apple), cell, GREEN);

  if (self->gameover) {
    char *message = "YOU DIED";
    DrawText(message, self->cell_width + 10, self->cell_width, 50, RED);
  }
}
