#include "hzpch.h"

#include "Application.h"


#include "Log.h"
#include "glad/glad.h"

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::s_Instance=nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance,"Application already exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

	}
	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlayer(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Runing = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Runing)
		{
			glClearColor(0,0,0,1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer:m_LayerStack)
			{
				layer->OnUpdate();
			}
			std::cout << "123";
			m_Window->OnUpdate();
		};
	}
}