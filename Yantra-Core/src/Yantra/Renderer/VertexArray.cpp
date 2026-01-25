#include "VertexArray.h"
#include <yqpch.h>

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Yantra {

VertexArray *VertexArray::Create() { return new OpenGLVertexArray(); }

} // namespace Yantra
