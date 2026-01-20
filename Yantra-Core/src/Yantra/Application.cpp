#include "yqpch.h"
#include "Application.h"
#include "Log.h"

namespace Yantra{

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        Log::Init();
        YANTRA_CORE_INFO("Yantra Initialized\n");

        m_Window = std::unique_ptr<Window>(Window::Create());

        m_Window->SetEventCallback(BIND_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        YANTRA_CORE_TRACE("Starting Run Loop");
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
        YANTRA_CORE_TRACE("Stopping Run Loop");
    }
    void Application::OnEvent(Event& e)
    {
        YANTRA_CORE_TRACE("{0}", e);

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}