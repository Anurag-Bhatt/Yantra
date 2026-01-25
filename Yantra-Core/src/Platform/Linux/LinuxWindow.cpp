#include "yqpch.h"

#ifdef __linux__

#include "LinuxWindow.h"

#include "Yantra/Events/ApplicationEvent.h"
#include "Yantra/Events/KeyEvent.h"
#include "Yantra/Events/MouseEvent.h"
#include "Yantra/Log.h"

#include <glad/glad.h>

namespace Yantra {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
  YANTRA_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

// THIS LINKS THE ABSTRACT WINDOW TO THIS IMPLEMENTATION
Window *Window::Create(const WindowProps &props) {
  return new LinuxWindow(props);
}

LinuxWindow::LinuxWindow(const WindowProps &props) { Init(props); }

LinuxWindow::~LinuxWindow() { Shutdown(); }

void LinuxWindow::Init(const WindowProps &props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.width;
  m_Data.Height = props.height;

  YANTRA_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.width,
                   props.height);

  if (!s_GLFWInitialized) {
    int success = glfwInit();
    // YANTRA_CORE_ASSERT(success, "Could not initialize GLFW!");
    if (!success)
      YANTRA_CORE_ERROR("Could not initialize GLFW!");

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow((int)props.width, (int)props.height,
                              m_Data.Title.c_str(), nullptr, nullptr);

  // --- OPENGL INITIALIZATION ---
  glfwMakeContextCurrent(m_Window);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  // YANTRA_CORE_ASSERT(status, "Failed to initialize Glad!");
  if (!status)
    YANTRA_CORE_ERROR("Failed to initialize Glad!");

  YANTRA_CORE_INFO("OpenGL Info:");
  YANTRA_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
  YANTRA_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
  YANTRA_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));

  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // --- EVENTS CALLBACKS ---

  // Resize
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

  // Close
  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  // Key
  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(key, 0);
      data.EventCallback(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      data.EventCallback(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(key, 1);
      data.EventCallback(event);
      break;
    }
    }
  });

  // Mouse Button
  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
        }
      });

  // Scroll
  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

  // Cursor Pos
  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
}

void LinuxWindow::Shutdown() { glfwDestroyWindow(m_Window); }

void LinuxWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void LinuxWindow::SetVSync(bool enabled) {
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool LinuxWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Yantra

#endif
