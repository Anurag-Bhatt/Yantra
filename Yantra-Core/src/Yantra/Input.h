#pragma once

#include "Yantra/Core.h"
#include "Yantra/Keycodes.h"
#include "Yantra/Mousecodes.h"

#include <X11/X.h>
#include <utility>

namespace Yantra {

class YANTRA_API Input {
public:
  static bool IsKeyPressed(KeyCode keycode);
  static bool IsMouseButtonPressed(MouseCode button);
  static std::pair<float, float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();
};
} // namespace Yantra
