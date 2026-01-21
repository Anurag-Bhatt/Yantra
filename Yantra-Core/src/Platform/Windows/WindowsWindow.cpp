#include "yqpch.h"

#include "WindowsWindow.h"
#include "Yantra/Log.h"

#include <glad/glad.h>

// Handling Events
#include "Yantra/Events/ApplicationEvent.h"
#include "Yantra/Events/MouseEvent.h"
#include "Yantra/Events/KeyEvent.h"


namespace Yantra {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int32 error, const char* description) 
	{
		YANTRA_CORE_ERROR("GLFW Error {0} {1}", error, description);
	}


	Window* Window::Create(const WindowProps& props) {
			
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& prop)
	{
		Init(prop);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) 
		{
			glfwSwapInterval(1);
		}
		else 
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;;
	}

	void WindowsWindow::Init(const WindowProps& prop)
	{
		m_Data.Title	= prop.Title;
		m_Data.height	= prop.height;
		m_Data.width	= prop.width;

		YANTRA_CORE_INFO("Creating window {0} ({1}) ({2})", prop.Title, prop.width, prop.height);

		if (!s_GLFWInitialized) 
		{
			int32 success = glfwInit();
			YANTRA_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
		}

		m_Window = glfwCreateWindow((int32)prop.width, (int32)prop.height, prop.Title.c_str(), nullptr, nullptr);

		if (m_Window == nullptr) 
		{
			YANTRA_CORE_ERROR("GLFW failed to create a window.");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		YANTRA_CORE_ASSERT(status, "Failed to initialized GLAD");

		YANTRA_CORE_INFO("OpenGL GPU Info:");
		YANTRA_CORE_INFO(" Vendor {0}", (const char*)glGetString(GL_VENDOR));
		YANTRA_CORE_INFO(" Renderer {0}", (const char*)glGetString(GL_RENDERER));
		YANTRA_CORE_INFO(" Version {0}", (const char*)glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_Window, &m_Data);

		SetVSync(true);

		// Set Callback functions for handling events

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
		
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}