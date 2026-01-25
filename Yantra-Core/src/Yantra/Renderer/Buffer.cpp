#include "Buffer.h"
#include <yqpch.h>

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Yantra {

VertexBuffer *VertexBuffer::Create(float *vertices, uint32 size) {
  return new OpenGLVertexBuffer(vertices, size);
}

IndexBuffer *IndexBuffer::Create(uint32 *indices, uint32 count) {
  return new OpenGLIndexBuffer(indices, count);
}
} // namespace Yantra
