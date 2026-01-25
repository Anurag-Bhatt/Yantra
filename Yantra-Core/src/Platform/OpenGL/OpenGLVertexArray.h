#pragma once

#include "Yantra/Core.h"
#include "Yantra/Renderer/Buffer.h"
#include "Yantra/Renderer/VertexArray.h"
#include <memory>
#include <vector>

namespace Yantra {

class YANTRA_API OpenGLVertexArray : public VertexArray {
public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void
  AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
  virtual void
  SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

  virtual const std::vector<std::shared_ptr<VertexBuffer>> &
  GetVertexBuffers() const override;
  virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override;

private:
  uint32 m_RendererID;
  std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
  std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

} // namespace Yantra
