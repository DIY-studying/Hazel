#include "hzpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include <imgui.h>
#include "GLFW/glfw3.h"
#include "Hazel/Render/Render.h"
#include "Hazel/Core.h"

namespace Hazel
{

	Application* Application::s_Instance=nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance,"Application already exist!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallBack(HZ_BIND_EVENT_FN(Application::OnEvent));

		Render::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlayer(m_ImGuiLayer);
	}
	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayer(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDisPatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

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
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimise = true;
			return false;
		}

		m_Minimise = false;
		Render::OnWindowResize(e.GetWidth(),e.GetHeight());

		return false;
	}

	void Application::Run()
	{
		while (m_Runing)
		{
			float time =(float)glfwGetTime();
			TimeStep timeStep=time-m_LastFramTime;
			m_LastFramTime = time;

			if (!m_Minimise)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timeStep);
				}
			}
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		};
	}
}