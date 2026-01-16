#pragma once

#include "Yantra/Core.h"

#ifdef YANTRA_PLATFORM_WINDOWS

extern Yantra::Application* Yantra::CreateApplication();

int main()
{
    auto app = Yantra::CreateApplication();

    app->Run();

    delete app;
    return 0;
}

#endif