#pragma once
#include "Yantra/Core.h"

#include "Window.h"
#include <memory>

namespace Yantra{

    class YANTRA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Client Side
    Application* CreateApplication();
}