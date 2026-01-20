#pragma once
#include "yqpch.h"
#include "Yantra/Core.h"
#include "Window.h"

#include <Yantra/Events/ApplicationEvent.h>

namespace Yantra{

    class YANTRA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

    private:

        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Client Side
    Application* CreateApplication();
}