#pragma once
#include "yqpch.h"

#include "Yantra/Core.h"

#include "Window.h"
#include <Yantra/LayerStack.h>
#include "Yantra/Events/Event.h"
#include <Yantra/Events/ApplicationEvent.h>

#include <Yantra/ImGui/ImGuiLayer.h>

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

        inline Window& GetWindow() { return *m_Window; }
        static inline Application& Get() { return *s_Instance; }
        float* GetClearColor() { return m_ClearCode; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        bool m_Running = true;
        LayerStack m_LayerStack;

        ImGuiLayer* m_ImGuiLayer;
        std::unique_ptr<Window> m_Window;
        static Application* s_Instance;

        float m_LastFrameTime = 0.0f;
        float m_ClearCode[4] = {1.0f, 0.0f, 1.0f, 1.0f};
    };

    // Client Side
    Application* CreateApplication();
}