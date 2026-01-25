#include "Platform/OpenGL/OpenGLBuffer.h"
#include "OpenGLBuffer.h"
#include "Yantra/Core.h"
#include <yqpch.h>

#include <glad/glad.h>

namespace Yantra {

// -- Vertex Buffer -- //
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32 size) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// -- Index Buffer -- //

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32 *indices, uint32 count) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(0, &m_RendererID); }

void OpenGLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Yantra
