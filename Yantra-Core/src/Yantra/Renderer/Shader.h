#pragma once

#include <Yantra/Core.h>
#include <filesystem>
#include <string>

namespace Yantra {

class YANTRA_API Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  // Load from files
  static Shader *Create(const std::filesystem::path &vertexPath,
                        const std::filesystem::path &fragmentPath);
  // Load from raw strings
  static Shader *Create(const std::string &vertexSrc,
                        const std::string &fragmentSrc);
};
} // namespace Yantra
