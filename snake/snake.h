#include "deque.h"
#include "raylib.h"

#ifndef SNAKE_H
#define SNAKE_H

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
