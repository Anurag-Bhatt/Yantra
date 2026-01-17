#include "Yantra/Application.h"
#include "Yantra/Log.h"

#include <Yantra/Events/ApplicationEvent.h>


namespace Yantra{

    Application::Application()
    {
        Log::Init();
        YANTRA_CORE_WARN("Yantra Initialized\n");

        WindowResizeEvent e(1280, 720);

        YANTRA_TRACE("{}", e);

        if (e.IsInCategory(EventCategoryApplication)) {

            YANTRA_INFO("Event: 'WindowResize' belongs to category Application!!");
        }

        if (e.IsInCategory(EventCategoryInput)) {
            YANTRA_ERROR("This should not Print, WindowResize is not an Input Event");
        }

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