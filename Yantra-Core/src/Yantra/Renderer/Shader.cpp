#include <cstddef>
#include <ios>
#include <yqpch.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Shader.h"
#include "Yantra/Log.h"

#include <fstream>
#include <sstream>

namespace Yantra {

static std::string ReadFile(const std::filesystem::path &filepath) {
  std::string result;
  std::ifstream in(filepath, std::ios::in | std::ios::binary);

  if (in) {
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    if (size != -1) {
      result.resize(size);
      in.seekg(0, std::ios::beg);
      in.read(&result[0], size);
    } else {
      YANTRA_CORE_ERROR("{Could not read from file {0}", filepath.string());
    }
  } else {
    YANTRA_CORE_ERROR("{Could not read from file {0}", filepath.string());
  }
  return result;
}

Shader *Shader::Create(const std::filesystem::path &vertexPath,
                       const std::filesystem::path &fragmentPath) {
  std::string vertexSrc = ReadFile(vertexPath);
  std::string fragSrc = ReadFile(fragmentPath);

  return new OpenGLShader(vertexSrc, fragSrc);
}

Shader *Shader::Create(const std::string &vertexSrc,
                       const std::string &fragmentSrc) {
  return new OpenGLShader(vertexSrc, fragmentSrc);
}

} // namespace Yantra
