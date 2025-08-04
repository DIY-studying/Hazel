#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"
#include "Hazel/Core/TimeStep.h"


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

		inline static Application& GetApp() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowClosedEvent&);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;

		
		float m_LastFramTime;
	};

	//define in client
	Application* CreatApplication();
}
