#pragma once

#include "Yantra/Core.h"
#include "Yantra/Renderer/RendererAPI.h"
#include "Yantra/Renderer/VertexArray.h"
#include <memory>
#include <sys/types.h>

namespace Yantra {

class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void Init() override;
  virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);

  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;

  virtual void
  DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};
} // namespace Yantra
