#include "OrthographicCameraController.h"

#include "Yantra/Core.h"
#include "Yantra/Events/ApplicationEvent.h"
#include "Yantra/Events/Event.h"
#include "Yantra/Events/MouseEvent.h"
#include "Yantra/Input.h"
#include "Yantra/Keycodes.h"
#include "Yantra/Timestep.h"
#include <X11/X.h>
#include <algorithm>

namespace Yantra {

OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool rotation)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
               -m_ZoomLevel, m_ZoomLevel) {}

void OrthographicCameraController::OnUpdate(TimeStep ts) {
  if (Input::IsKeyPressed(KeyCode::A)) {
    m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
  }

  else if (Input::IsKeyPressed(KeyCode::D)) {
    m_CameraPosition.x += m_CameraTranslationSpeed * ts;
  }

  if (Input::IsKeyPressed(KeyCode::W)) {
    m_CameraPosition.y += m_CameraTranslationSpeed * ts;
  }

  else if (Input::IsKeyPressed(KeyCode::S)) {
    m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
  }

  // Rotate Camera
  if (m_Rotation) {
    if (Input::IsKeyPressed(KeyCode::Q)) {
      m_CameraRotation += m_CameraRotationSpeed * ts;
    }

    if (Input::IsKeyPressed(KeyCode::E)) {
      m_CameraRotation -= m_CameraRotationSpeed * ts;
    }
  }

  m_Camera.SetPosition(m_CameraPosition);

  m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(
      YANTRA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      YANTRA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &event) {
  m_ZoomLevel -= event.GetYOffset() * 0.25f;
  m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

  m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel,
                               m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                               m_ZoomLevel);
  return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &event) {

  m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();

  m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel,
                               m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                               m_ZoomLevel);
  return false;
}

} // namespace Yantra
