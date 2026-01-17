#include "Yantra/Application.h"
#include "Yantra/Log.h"

namespace Yantra{

    Application::Application()
    {
        Log::Init();
        YANTRA_CORE_WARN("Yantra Initialized\n");
        YANTRA_INFO("Client says Hello\n");
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {

        while(true)
        {
            break;
        }
    }
}