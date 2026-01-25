#pragma once

#include "Yantra/Renderer/Shader.h"

namespace Yantra {

class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
  virtual ~OpenGLShader();

  virtual void Bind() const override;
  virtual void Unbind() const override;

private:
  uint32 m_RendererID;
};

} // namespace Yantra
