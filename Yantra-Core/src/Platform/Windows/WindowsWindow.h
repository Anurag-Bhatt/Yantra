#pragma once

#include <Yantra/Window.h>
#include <GLFW/glfw3.h>

namespace Yantra {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& prop);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint32 GetWidth()	const override { return m_Data.width; }
		inline uint32 GetHeight()	const override { return m_Data.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual void* GetNativeWindow() const override { return m_Window; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:

		virtual void Init(const WindowProps& prop);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData 
		{
			std::string Title;
			uint32 width, height;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}