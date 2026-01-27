#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Yantra {
RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
