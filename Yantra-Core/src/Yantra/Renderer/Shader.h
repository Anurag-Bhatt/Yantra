#pragma once

#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <Yantra/Core.h>
#include <filesystem>
#include <string>

#include <glm/glm.hpp>

namespace Yantra {

class YANTRA_API Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void UploadUniformInt(const std::string &name, uint32 value) = 0;

  virtual void UploadUniformFloat(const std::string &name, float value) = 0;

  virtual void UploadUniformFloat2(const std::string &name,
                                   const glm::vec2 &value) = 0;
  virtual void UploadUniformFloat3(const std::string &name,
                                   const glm::vec3 &value) = 0;
  virtual void UploadUniformFloat4(const std::string &name,
                                   const glm::vec4 &value) = 0;

  virtual void UploadUniformMat3(const std::string &name,
                                 const glm::mat3 &value) = 0;
  virtual void UploadUniformMat4(const std::string &name,
                                 const glm::mat4 &value) = 0;

  // Load from files
  static Shader *Create(const std::filesystem::path &vertexPath,
                        const std::filesystem::path &fragmentPath);
  // Load from raw strings
  static Shader *Create(const std::string &vertexSrc,
                        const std::string &fragmentSrc);
};
} // namespace Yantra
