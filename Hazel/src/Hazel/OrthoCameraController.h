#pragma once

#include "Hazel/Render/gameobject/Camera.h"
#include "Hazel/Core/Time.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool isRation =false);

		void OnEvent(Event& e);
		void OnUpdate(TimeStep ts);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }

		float GetZoom() { return m_ZoomLevel; }

	private:
		bool OnMourseScoll(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:

		// Atention initial order
		float m_AspectRatio;
		float m_ZoomLevel;
		OrthoCamera m_Camera;
		
		Eigen::Vector3f m_Position;
		float m_angle;
		bool m_IsRation;

		float m_RotateSpeed = 2.0f , m_MoveSpeed = 5.0f;

	};

}