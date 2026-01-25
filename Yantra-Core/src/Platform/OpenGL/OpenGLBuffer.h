#pragma once

#include "Yantra/Core.h"
#include "Yantra/Renderer/Buffer.h"

namespace Yantra {

class OpenGLVertexBuffer : public VertexBuffer {
public:
  OpenGLVertexBuffer(float *vertices, uint32 size);
  virtual ~OpenGLVertexBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual const BufferLayout &GetLayout() const override { return m_Layout; }
  virtual void SetLayout(BufferLayout &layout) override { m_Layout = layout; }

private:
  uint32 m_RendererID;
  BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
  OpenGLIndexBuffer(uint32 *indices, uint32 count);
  virtual ~OpenGLIndexBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual uint32 GetCount() const override { return m_Count; }

private:
  uint32 m_RendererID;
  uint32 m_Count;
};

} // namespace Yantra
