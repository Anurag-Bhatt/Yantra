#include "OpenGLRendererAPI.h"
#include "Yantra/Core.h"

#include <glad/glad.h>
#include <memory>

namespace Yantra {

void OpenGLRendererAPI::Init() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void OpenGLRendererAPI::SetViewport(uint32 x, uint32 y, uint32 width,
                                    uint32 height) {
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(
    const std::shared_ptr<VertexArray> &vertexArray) {
  glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(),
                 GL_UNSIGNED_INT, nullptr);
}
} // namespace Yantra
