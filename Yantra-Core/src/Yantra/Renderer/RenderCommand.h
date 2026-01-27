#pragma once

#include "RendererAPI.h"
#include "Yantra/Core.h"
#include <memory>

namespace Yantra {

class RenderCommand {
public:
  inline static void Init() { s_RendererAPI->Init(); }

  inline static void SetViewport(uint32 x, uint32 y, uint32 width,
                                 uint32 height) {
    s_RendererAPI->SetViewport(x, y, width, height);
  }

  inline static void SetClearColor(const glm::vec4 &color) {
    s_RendererAPI->SetClearColor(color);
  }

  inline static void Clear() { s_RendererAPI->Clear(); }

  inline static void
  DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
    s_RendererAPI->DrawIndexed(vertexArray);
  }

private:
  static RendererAPI *s_RendererAPI;
};

} // namespace Yantra
