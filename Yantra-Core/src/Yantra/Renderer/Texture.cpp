#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"
#include "Yantra/Core.h"
#include <memory>

namespace Yantra {

std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    YANTRA_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLTexture>(path);
  }

  YANTRA_CORE_ASSERT(false, "Unknown RendererAPI");
  return nullptr;
}

} // namespace Yantra
