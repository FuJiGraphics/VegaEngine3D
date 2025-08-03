#pragma once

// Code Reference By https://github.com/TheCherno/Hazel.git

#include "Event.h"

namespace vega {

	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return static_cast<int>(m_KeyCode); }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyType keycode)
			: m_KeyCode(keycode) {}

		KeyType m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyType keycode, unsigned int repeatCount = 0)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline unsigned int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		unsigned int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyType keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};


	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyType keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

} // namepsace fz