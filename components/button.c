#include "button.h"
#include "raylib.h"

ButtonState GetButtonState(Rectangle button) {
  ButtonState state;
  Vector2 mousePos = GetMousePosition();

  if (CheckCollisionPointRec(mousePos, button)) {
    state = BUTTON_HOVERED;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      state = BUTTON_PRESSED;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      state = BUTTON_ACTIVATED;
    }
  } else {
    state = BUTTON_IDLE;
  }

  return state;
}
