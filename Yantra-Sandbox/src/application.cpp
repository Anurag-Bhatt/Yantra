#include "Yantra/Log.h"
#include "Yantra/Renderer/RenderCommand.h"
#include "Yantra/Renderer/Renderer.h"
#include "Yantra/Renderer/Texture.h"
#include "Yantra/Timestep.h"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Platform/OpenGL/OpenGLTexture.h>
#include <Yantra.h>
#include <Yantra/Core.h>
#include <Yantra/Renderer/OrthographicCamera.h>
#include <Yantra/Renderer/OrthographicCameraController.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <memory>

class ExampleLayer : public Yantra::Layer {
public:
  ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {

    YANTRA_INFO("ExampleLayer: Creating VertexArray");
    m_VertexArray.reset(Yantra::VertexArray::Create());

    float vertices[5 * 4] = {
        // Position (X, Y, Z)    // TexCoord (U, V)
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Bottom Right
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Top Right
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // Top Left
    };

    std::shared_ptr<Yantra::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(
        Yantra::VertexBuffer::Create(vertices, sizeof(vertices)));

    Yantra::BufferLayout layout = {
        {Yantra::ShaderDataType::Float3, "a_Position", true},
        {Yantra::ShaderDataType::Float2, "a_TexCoord", true}};

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    Yantra::uint32 indices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<Yantra::IndexBuffer> indexBuffer;
    indexBuffer.reset(Yantra::IndexBuffer::Create(
        indices, sizeof(indices) / sizeof(Yantra::uint32)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            out vec2 v_TexCoord;
            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
    std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec2 v_TexCoord;
            uniform sampler2D u_Texture; 
            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

    m_Shader.reset(Yantra::Shader::Create(vertexSrc, fragmentSrc));
    if (!m_Shader) {
      YANTRA_ERROR("ExampleLayer: Shader creation Failed");
    }

    // m_Texture =
    // Yantra::Texture2D::Create("assets/textures/Yellow_Heart.jpg");
    //  m_Texture = Yantra::Texture2D::Create("assets/textures/Mushroom.png");
    m_Texture = Yantra::Texture2D::Create("assets/textures/CheckerBoard.jpg");

    if (!m_Texture) {
      YANTRA_ERROR("Failed to load texture");
      return;
    }

    std::dynamic_pointer_cast<Yantra::OpenGLShader>(m_Shader)->Bind();

    std::dynamic_pointer_cast<Yantra::OpenGLShader>(m_Shader)->UploadUniformInt(
        "u_Texture", 0);
  }

  void OnUpdate(Yantra::TimeStep timestep) override {

    m_CameraController.OnUpdate(timestep);

    // Set Background
    Yantra::RenderCommand::SetClearColor(glm::vec4(m_BackgroundColor, 1.0f));
    Yantra::RenderCommand::Clear();

    Yantra::Renderer::BeginScene(m_CameraController.GetCamera());

    m_Texture->Bind();
    // m_Shader->Bind();
    // m_Shader->UploadUniformFloat3("u_Color", m_TriangleColor);

    Yantra::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
    Yantra::Renderer::EndScene();
  }

  virtual void OnImGuiRender() override {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Triangle Color", glm::value_ptr(m_TriangleColor));
    ImGui::ColorEdit3("Background Color", glm::value_ptr(m_BackgroundColor));
    ImGui::End();
  }

  void OnEvent(Yantra::Event &event) override {
    // YANTRA_TRACE("{0}", event);
    m_CameraController.OnEvent(event);
  }

private:
  std::shared_ptr<Yantra::Shader> m_Shader;
  std::shared_ptr<Yantra::VertexArray> m_VertexArray;
  std::shared_ptr<Yantra::Texture2D> m_Texture;

  Yantra::OrthographicCameraController m_CameraController;

  // color
  glm::vec3 m_TriangleColor = {0.4f, 0.3f, 0.6f};
  glm::vec3 m_BackgroundColor = {0.6f, 0.2f, 0.7f};
};

class Sandbox : public Yantra::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer); }

  ~Sandbox() {}
};

Yantra::Application *Yantra::CreateApplication() { return new Sandbox(); }
