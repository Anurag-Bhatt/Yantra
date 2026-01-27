#pragma once

#include "OrthographicCamera.h"
#include "Yantra/Events/ApplicationEvent.h"
#include "Yantra/Events/Event.h"
#include "Yantra/Events/MouseEvent.h"
#include "Yantra/Timestep.h"

namespace Yantra {

class OrthographicCameraController {
public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  void OnUpdate(TimeStep ts);
  void OnEvent(Event &e);

  OrthographicCamera &GetCamera() { return m_Camera; }
  const OrthographicCamera &GetCamera() const { return m_Camera; }

  float GetZoomLevel() const { return m_ZoomLevel; }
  void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &event);
  bool OnWindowResized(WindowResizeEvent &event);

private:
  float m_AspectRatio;
  float m_ZoomLevel = 1.0f;
  OrthographicCamera m_Camera;

  bool m_Rotation;
  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  float m_CameraRotation = 0.0f;

  float m_CameraTranslationSpeed = 5.0f;
  float m_CameraRotationSpeed = 5.0f;
};

} // namespace Yantra
