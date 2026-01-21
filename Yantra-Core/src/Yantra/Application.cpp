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

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

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