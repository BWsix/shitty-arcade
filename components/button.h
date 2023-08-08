#include "raylib.h"

#ifndef BUTTON_H
#define BUTTON_H

typedef enum ButtonState {
  BUTTON_IDLE,
  BUTTON_HOVERED,
  BUTTON_PRESSED,
  BUTTON_ACTIVATED,
} ButtonState;

ButtonState GetButtonState(Rectangle rect, MouseButton mouseButton);

#endif // !BUTTON_H
