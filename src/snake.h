#ifndef SNAKE_H
#define SNAKE_H

#include "deque.h"
#include "raylib.h"

typedef enum Direction {
  North,
  East,
  South,
  West,
} Direction;

typedef struct Snake {
  Deque *body;
  Direction heading;
} Snake;

Snake *Snake_create();
void Snake_destroy(Snake *snake);

bool Snake_change_heading(Snake *snake, Direction dir);

Vector2 Snake_get_next_cell(Snake *snake);

bool Snake_contains(Snake *snake, Vector2 cell);
void Snake_grow(Snake *snake, Vector2 cell);
void Snake_move(Snake *snake, Vector2 cell);

#endif // !SNAKE_H

#ifdef SNAKE_IMPLEMENTATION
#include <stdlib.h>

#ifdef DEQUE_IMPLEMENTATION
#define DEQUE_IMPLEMENTATION
#include "deque.h"
#endif 

Snake *Snake_create() {
  Snake *snake = malloc(sizeof(Snake));
  snake->heading = East;
  snake->body = Deque_create();

  int x_indices[] = {1, 2, 3};
  for (int i = 0; i < 3; i++) {
    Vector2 *cell = malloc(sizeof(Vector2));
    cell->x = x_indices[i];
    cell->y = 1;
    Deque_pushfront(snake->body, cell);
  }
  return snake;
}

void Snake_destroy(Snake *self) {
  Deque_destroy_values(self->body);
  Deque_destroy(self->body);
  free(self);
}

bool Snake_change_heading(Snake *self, Direction dir) {
  if (dir % 2 == self->heading % 2) { // cannot do 180
    return false;
  }
  self->heading = dir;
  return true;
}

Vector2 Snake_get_next_cell(Snake *self) {
  Vector2 head = *(Vector2 *)Deque_front(self->body);

  switch (self->heading) {
  case North:
    head.y -= 1;
    break;
  case East:
    head.x += 1;
    break;
  case South:
    head.y += 1;
    break;
  case West:
    head.x -= 1;
    break;
  }

  return head;
}

bool Snake_contains(Snake *self, Vector2 cell) {
  for (int i = 0; i < Deque_size(self->body); i++) {
    Vector2 *body = (Vector2 *)Deque_at(self->body, i);
    if (body->x == cell.x && body->y == cell.y) {
      return true;
    }
  }
  return false;
}

void Snake_grow(Snake *self, Vector2 cell) {
  Vector2 *head = malloc(sizeof(Vector2));
  head->x = cell.x;
  head->y = cell.y;
  Deque_pushfront(self->body, head);
}

void Snake_move(Snake *self, Vector2 cell) {
  Vector2 *head = Deque_popback(self->body); // reuse memory
  head->x = cell.x;
  head->y = cell.y;
  Deque_pushfront(self->body, head);
}
#endif // !SNAKE_IMPLEMENTATION
