#include <Yantra.h>

class Sandbox : public Yantra::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Yantra::Application* Yantra::CreateApplication()
{
    return new Sandbox();
}