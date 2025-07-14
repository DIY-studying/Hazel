#include "hzpch.h"

#include "Application.h"


#include "Log.h"
#include"GLFW/glfw3.h"
namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		HZ_CORE_TRACE("{0}", e.ToString());
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
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		};
	}
}