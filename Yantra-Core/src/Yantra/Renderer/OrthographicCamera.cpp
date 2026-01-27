#include "OrthographicCamera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/matrix.hpp"
#include <yqpch.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Yantra {

OrthographicCamera::OrthographicCamera(float left, float right, float top,
                                       float bottom)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_ViewMatrix(1.0f) {
  m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation),
                                    glm::vec3(0, 0, 1));

  m_ViewMatrix = glm::inverse(transform);

  m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace Yantra
