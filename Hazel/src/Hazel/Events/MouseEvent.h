#pragma once

#include "Event.h"

#include"hzpch.h"

namespace Hazel
{
	class HAZEL_API MouseMoveEvent :public Event
	{
	public:
		MouseMoveEvent(float x, float y) :m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent" << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CALSS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class HAZEL_API MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(float xOffset,float yOffset):m_XOffset(xOffset),m_YOffset(yOffset){}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYoffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent" << GetXOffset() << "," << GetYoffset();
			return ss.str();
		}

		EVENT_CALSS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class HAZEL_API MouseButtonEvent :public Event
	{
	public:
		inline float GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventMouseButton | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) :m_Button(button) {}

		int m_Button;
	};

	class HAZEL_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent" << m_Button;
			return ss.str();
		}

		EVENT_CALSS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseButtonRelaesedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonRelaesedEvent(int button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonRelaesedEvent " << m_Button;
			return ss.str();
		}

		EVENT_CALSS_TYPE(MouseButtonReleased)
	};
}