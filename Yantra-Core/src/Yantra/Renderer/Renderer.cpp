#include "Yantra/Renderer/Renderer.h"
#include "RendererAPI.h"
#include "Yantra/Renderer/OrthographicCamera.h"
#include "Yantra/Renderer/RenderCommand.h"
#include <yqpch.h>

namespace Yantra {

Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

void Init() { RenderCommand::Init(); }

void Renderer::OnWindowResize(uint32 width, uint32 height) {
  RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(OrthographicCamera &camera) {
  // Setup scene - Camera, lights
  s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertexArray,
                      const glm::mat4 &transform) {
  shader->Bind();

  shader->UploadUniformMat4("u_ViewProjectionMatrix",
                            s_SceneData->ViewProjectionMatrix);

  shader->UploadUniformMat4("u_Transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::Shutdown() { delete s_SceneData; }

} // namespace Yantra
