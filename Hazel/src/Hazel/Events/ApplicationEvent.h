#pragma once

#include"Event.h"

#include"hzpch.h"    

namespace Hazel
{
	class HAZEL_API WindowResizeEvent:public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :m_Width(width), m_Height(height) {};

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		EVENT_CALSS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class HAZEL_API WindowClosedEvent :public Event
	{
	public:
		WindowClosedEvent()  {};

		EVENT_CALSS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class HAZEL_API AppTickEvent :public Event
	{
	public:
		AppTickEvent() {};

		EVENT_CALSS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class HAZEL_API AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() {};

		EVENT_CALSS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class HAZEL_API AppRenderEvent :public Event
	{
	public:
		AppRenderEvent() {};

		EVENT_CALSS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}