#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event&);
	private:
		bool OnWindowClose(WindowClosedEvent&);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
	};

	//define in client
	Application* CreatApplication();
}
