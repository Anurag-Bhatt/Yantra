#pragma once
#include "Yantra/Core.h"

namespace Yantra{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}