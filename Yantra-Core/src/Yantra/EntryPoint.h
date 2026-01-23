#pragma once

#include "Yantra/Core.h"

#if defined(YANTRA_PLATFORM_WINDOWS) || defined(YANTRA_PLATFORM_LINUX)

extern Yantra::Application *Yantra::CreateApplication();

int main() {
  auto app = Yantra::CreateApplication();

  app->Run();

  delete app;
  return 0;
}

#endif
