#include "yqpch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>

namespace Yantra{

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        YANTRA_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        Log::Init();    
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // Testing - Red Color
        m_ClearCode[0] = 1.0f;
        m_ClearCode[1] = 0.0f;
        m_ClearCode[2] = 0.0f;
        m_ClearCode[3] = 1.0f;

        YANTRA_CORE_INFO("Yantra Initialized\n");
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();   
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));

        // Send event e to all the layers until it is handled
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {

            (*--it)->OnEvent(e);
            if (e.m_Handled) {
                break;
            }
        }
        YANTRA_CORE_TRACE("{0}", e);
    }

    void Application::Run()
    {
        YANTRA_CORE_TRACE("Starting Run Loop");
        while(m_Running)
        {
            // Using ImGui to send bg color to render
            glClearColor(m_ClearCode[0], m_ClearCode[1], m_ClearCode[2], m_ClearCode[3]);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : m_LayerStack) 
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) 
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
        YANTRA_CORE_TRACE("Stopping Run Loop");
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}