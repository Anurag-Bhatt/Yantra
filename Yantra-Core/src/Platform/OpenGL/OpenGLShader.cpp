#include "OpenGLShader.h"
#include "Yantra/Core.h"
#include "Yantra/Log.h"
#include <yqpch.h>

#include <glad/glad.h>
#include <vector>

namespace Yantra {

OpenGLShader::OpenGLShader(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *source = (const GLchar *)vertexSrc.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  glCompileShader(vertexShader);

  GLint is_compiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint maxLength = 0;

    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(vertexShader);

    YANTRA_CORE_ERROR("{0}", infoLog.data());
    YANTRA_CORE_ASSERT(false, "Vertex Shader Compilation Failed");
    return;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  source = (const GLchar *)fragmentSrc.c_str();
  glShaderSource(fragmentShader, 1, &source, 0);

  glCompileShader(fragmentShader);

  is_compiled = 0;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint maxLength = 0;

    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(fragmentShader);

    YANTRA_CORE_ERROR("{0}", infoLog.data());
    YANTRA_CORE_ASSERT(false, "Fragment Shader Compilation Failed");
    return;
  }

  m_RendererID = glCreateProgram();
  glAttachShader(m_RendererID, vertexShader);
  glAttachShader(m_RendererID, fragmentShader);

  glLinkProgram(m_RendererID);

  GLint is_linked = 0;
  glGetProgramiv(m_RendererID, GL_LINK_STATUS, &is_linked);
  if (is_linked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(m_RendererID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    YANTRA_CORE_ERROR("{0}", infoLog.data());
    YANTRA_CORE_ASSERT(false, "Shader link failure");
    return;
  }

  glDetachShader(m_RendererID, vertexShader);
  glDetachShader(m_RendererID, fragmentShader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_RendererID); }

void OpenGLShader::Bind() const { glUseProgram(m_RendererID); }

void OpenGLShader::Unbind() const { glUseProgram(0); }
} // namespace Yantra
