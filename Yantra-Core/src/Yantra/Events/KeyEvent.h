#pragma once

#include "Event.h"
#include <sstream>

namespace Yantra
{
	class YANTRA_API KeyEvent : public Event
	{
	public:
		inline int32 GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:

		KeyEvent(int32 keycode)
			:m_KeyCode(keycode) {}

		int32 m_KeyCode;
	};

	class YANTRA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline uint32 GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int32 m_RepeatCount;
	};

	class YANTRA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32 keyCode) 
		: KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}