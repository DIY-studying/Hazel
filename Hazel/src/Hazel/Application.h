#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);

	private:
		bool OnWindowClose(WindowClosedEvent&);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;

		LayerStack m_LayerStack;
	};

	//define in client
	Application* CreatApplication();
}
