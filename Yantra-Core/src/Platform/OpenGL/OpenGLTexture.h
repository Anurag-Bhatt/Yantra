#pragma once

#include "Yantra/Core.h"
#include "Yantra/Renderer/Texture.h"
#include <glad/glad.h>

namespace Yantra {

class OpenGLTexture : public Texture2D {
public:
  OpenGLTexture(const std::string &path);
  virtual ~OpenGLTexture();

  virtual uint32 GetWidth() const override { return m_Width; }
  virtual uint32 GetHeight() const override { return m_Height; }

  virtual void Bind(uint32 slot = 0) const override;

private:
  std::string m_Path;
  uint32 m_Width, m_Height;
  uint32 m_RendererID;
  GLenum m_InternalFormat, m_DataFormat;
};

} // namespace Yantra
