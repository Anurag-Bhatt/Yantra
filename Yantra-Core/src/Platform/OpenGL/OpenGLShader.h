#pragma once

#include "Yantra/Renderer/Shader.h"

namespace Yantra {

class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
  virtual ~OpenGLShader();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void UploadUniformInt(const std::string &name, uint32 value) override;

  virtual void UploadUniformFloat(const std::string &name,
                                  float value) override;

  virtual void UploadUniformFloat2(const std::string &name,
                                   const glm::vec2 &value) override;
  virtual void UploadUniformFloat3(const std::string &name,
                                   const glm::vec3 &value) override;
  virtual void UploadUniformFloat4(const std::string &name,
                                   const glm::vec4 &value) override;

  virtual void UploadUniformMat3(const std::string &name,
                                 const glm::mat3 &value) override;
  virtual void UploadUniformMat4(const std::string &name,
                                 const glm::mat4 &value) override;

private:
  uint32 m_RendererID;
};

} // namespace Yantra
