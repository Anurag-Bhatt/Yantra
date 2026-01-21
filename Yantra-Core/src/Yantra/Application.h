#pragma once
#include "yqpch.h"

#include "Yantra/Core.h"

#include "Window.h"
#include <Yantra/LayerStack.h>
#include "Yantra/Events/Event.h"
#include <Yantra/Events/ApplicationEvent.h>


namespace Yantra{

    class YANTRA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:

        bool OnWindowClose(WindowCloseEvent& e);

        bool m_Running = true;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;
    };

    // Client Side
    Application* CreateApplication();
}