
#include "Yantra/Application.h"
#include "Yantra/Input.h"
#include "Yantra/Keycodes.h"
#include "Yantra/Mousecodes.h"
#include "yqpch.h"

#include <GLFW/glfw3.h>
#include <X11/X.h>

namespace Yantra {

bool Input::IsKeyPressed(KeyCode keycode) {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetKey(window, static_cast<int32>(keycode));
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetMouseButton(window, static_cast<int32>(button));
  return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition() {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  return {(float)xPos, (float)yPos};
}

float Input::GetMouseX() {
  auto [x, y] = GetMousePosition();
  return x;
}

float Input::GetMouseY() {
  auto [x, y] = GetMousePosition();
  return y;
}

} // namespace Yantra
