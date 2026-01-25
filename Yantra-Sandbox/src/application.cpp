#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <Yantra.h>
#include <Yantra/Core.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <memory>

class ExampleLayer : public Yantra::Layer {
public:
  ExampleLayer() : Layer("Example") {
    m_VertexArray.reset(Yantra::VertexArray::Create());

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f, // Bottom Left
        0.5f,  -0.5f, 0.0f, // Bottom Right
        0.0f,  0.5f,  0.0f  // Top Center
    };

    std::shared_ptr<Yantra::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(
        Yantra::VertexBuffer::Create(vertices, sizeof(vertices)));

    Yantra::BufferLayout layout = {
        {Yantra::ShaderDataType::Float3, "a_Position", true}};

    vertexBuffer->SetLayout(layout);

    m_VertexArray->AddVertexBuffer(vertexBuffer);

    Yantra::uint32 indices[3] = {0, 1, 2};

    std::shared_ptr<Yantra::IndexBuffer> indexBuffer;
    indexBuffer.reset(Yantra::IndexBuffer::Create(
        indices, sizeof(indices) / sizeof(Yantra::uint32)));

    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexSrc = R"(#version 330 core
    layout(location = 0) in vec3 a_Position;
    void main() {
    gl_Position = vec4(a_Position, 1.0);
    })";

    std::string fragmentSrc = R"(#version 330 core
    layout(location = 0) out vec4 color;
    uniform vec3 u_Color;
    void main() {
    color = vec4(u_Color, 1.0);
    })";
    m_Shader.reset(Yantra::Shader::Create(vertexSrc, fragmentSrc));
  }

  void OnUpdate() override {

    glClearColor(m_BackgroundColor[0], m_BackgroundColor[1],
                 m_BackgroundColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shader->Bind();

    m_Shader->UploadUniformFloat3("u_Color", m_TriangleColor);

    m_VertexArray->Bind();

    glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);
  }

  virtual void OnImGuiRender() override {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Triangle Color", glm::value_ptr(m_TriangleColor));
    ImGui::ColorEdit3("Background Color", glm::value_ptr(m_BackgroundColor));
    ImGui::End();
  }

  void OnEvent(Yantra::Event &event) override { YANTRA_TRACE("{0}", event); }

private:
  std::shared_ptr<Yantra::Shader> m_Shader;
  std::shared_ptr<Yantra::VertexArray> m_VertexArray;

  // color
  glm::vec3 m_TriangleColor = {0.4f, 0.3f, 0.6f};
  glm::vec3 m_BackgroundColor = {0.6f, 0.2f, 0.7f};
  //
};

class Sandbox : public Yantra::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer); }

  ~Sandbox() {}
};

Yantra::Application *Yantra::CreateApplication() { return new Sandbox(); }
