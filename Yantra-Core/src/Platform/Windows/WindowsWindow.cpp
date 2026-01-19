#include "yqpch.h"
#include "WindowsWindow.h"

#include "Yantra/Log.h"

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

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Red + Blue = Pink
		glClear(GL_COLOR_BUFFER_BIT);

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
		}

		m_Window = glfwCreateWindow((int32)prop.width, (int32)prop.height, prop.Title.c_str(), nullptr, nullptr);

		if (m_Window == nullptr) 
		{
			YANTRA_CORE_ERROR("GLFW failed to create a window.");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}