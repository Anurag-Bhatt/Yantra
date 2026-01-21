#include <Yantra.h>

class ExampleLayer : public Yantra::Layer 
{
public:

    ExampleLayer()
    :Layer("Example") 
    {
    }

    void OnUpdate() override
    {
        YANTRA_INFO("ExampleLayer::Update");
    }

    void OnEvent(Yantra::Event& event)
    {
        YANTRA_TRACE("{0}", event);
    }

};

class Sandbox : public Yantra::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer);
    }

    ~Sandbox()
    {

    }
};

Yantra::Application* Yantra::CreateApplication()
{
    return new Sandbox();
}