#pragma once

#include <yqpch.h>

#include "Yantra/Core.h"
#include "Yantra/Events/Event.h"

namespace Yantra {

	struct WindowProps
	{
		std::string Title;
		uint32 width;
		uint32 height;

		WindowProps(const std::string& _title = "Yantra Engine",
			uint32 _width = 1280,
			uint32 _height = 720)
			:Title(_title), width(_width), height(_height)
		{
		}
	};
	
	class YANTRA_API Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32 GetHeight() const = 0;
		virtual uint32 GetWidth() const = 0;

		virtual void* GetNativeWindow() const = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};
}