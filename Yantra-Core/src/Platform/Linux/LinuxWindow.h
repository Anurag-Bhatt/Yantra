#pragma once

#include "Yantra/Core.h"
#include "Yantra/Window.h"
#include <GLFW/glfw3.h>

namespace Yantra {

class LinuxWindow : public Window {
public:
  LinuxWindow(const WindowProps &props);
  virtual ~LinuxWindow();

  void OnUpdate() override;

  inline uint32 GetWidth() const override { return m_Data.Width; }
  inline uint32 GetHeight() const override { return m_Data.Height; }

  // Window attribute
  inline void SetEventCallback(const EventCallbackFn &callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  inline void *GetNativeWindow() const override { return m_Window; }

private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

private:
  GLFWwindow *m_Window;

  struct WindowData {
    std::string Title;
    uint32 Width, Height;
    bool VSync;

    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};

} // namespace Yantra
