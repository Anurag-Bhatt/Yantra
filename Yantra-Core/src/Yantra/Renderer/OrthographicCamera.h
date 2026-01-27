#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include <glm/glm.hpp>

namespace Yantra {

class OrthographicCamera {
public:
  OrthographicCamera(float left, float right, float top, float bottom);

  void SetPosition(const glm::vec3 &position) {
    m_Position = position;
    RecalculateViewMatrix();
  }
  const glm::vec3 &GetPosition() const { return m_Position; }

  void SetRotation(const float rotation) {
    m_Rotation = rotation;
    RecalculateViewMatrix();
  }
  float GetRotation() { return m_Rotation; }

  const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
  const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
  const glm::mat4 &GetViewProjectionMatrix() const {
    return m_ViewProjectionMatrix;
  }

private:
  void RecalculateViewMatrix();

private:
  glm::mat4 m_ProjectionMatrix;
  glm::mat4 m_ViewMatrix;
  glm::mat4 m_ViewProjectionMatrix;

  glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
  float m_Rotation = 0.0f;
};

} // namespace Yantra
