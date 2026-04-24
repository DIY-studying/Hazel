#include "hzpch.h"
#include "OrthoCameraController.h"

#include "Hazel/Input/Input.h"
#include "Hazel/Input/KeyCode.h"

namespace Hazel {

	OrthoCameraController::OrthoCameraController(float aspectRatio, bool isRation)
		:m_AspectRatio(aspectRatio), m_ZoomLevel(1.0f), 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_IsRation(isRation),m_Position(0), m_angle(0)
	{
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDisPatcher dispatch(e);
		dispatch.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthoCameraController::OnMourseScoll));
		dispatch.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthoCameraController::OnWindowResize));
	}

	void OrthoCameraController::OnUpdate(TimeStep ts)
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_Position.y -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_Position.y += m_MoveSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_Position.x -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_Position.x += m_MoveSpeed * ts;

		if (m_IsRation)
		{
			if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
				m_angle -= m_RotateSpeed * ts;
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
				m_angle += m_RotateSpeed * ts;
		}

		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_angle);
	}

	bool OrthoCameraController::OnMourseScoll(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYoffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjectMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio =(float) e.GetWidth() / e.GetHeight();
		m_Camera.SetProjectMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}