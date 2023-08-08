#include "button.h"
#include "raylib.h"

ButtonState GetButtonState(Rectangle button, MouseButton mouseButton) {
  ButtonState state;
  Vector2 mousePos = GetMousePosition();

  if (CheckCollisionPointRec(mousePos, button)) {
    state = BUTTON_HOVERED;
    if (IsMouseButtonDown(mouseButton)) {
      state = BUTTON_PRESSED;
    }
    if (IsMouseButtonReleased(mouseButton)) {
      state = BUTTON_ACTIVATED;
    }
  } else {
    state = BUTTON_IDLE;
  }

  return state;
}
