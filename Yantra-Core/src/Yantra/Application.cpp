#include "yqpch.h"

#include "Application.h"
#include "Log.h"


namespace Yantra{

    Application::Application()
    {
        Log::Init();
        YANTRA_CORE_WARN("Yantra Initialized\n");

        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        YANTRA_CORE_INFO("Starting Run Loop");
        while(m_Running)
        {
            //YANTRA_CORE_INFO("Updating...");
            m_Window->OnUpdate();
        }
        YANTRA_CORE_INFO("Stopping Run Loop");
    }
}