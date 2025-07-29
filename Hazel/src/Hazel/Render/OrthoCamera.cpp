#include "hzpch.h"
#include "OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: m_ProjectMatrix(glm::ortho(left, right, bottom, top, zNear, zFar)), m_angle(0), m_Position({0,0,0})
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectMatrix = m_ProjectMatrix*m_ViewMatrix;
	}

	void OrthoCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Position) * glm::rotate(glm::mat4(1.0f),glm::radians(m_angle),glm::vec3(0,0,1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}


}