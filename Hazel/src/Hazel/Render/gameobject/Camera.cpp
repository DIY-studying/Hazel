#include "hzpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Hazel
{
	//////////////////////////////////////////////////////////////////////////////////
	/// OrthoCamera //////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: m_ProjectMatrix(glm::ortho(left, right, bottom, top, zNear, zFar)), m_angle(0), m_Position({0,0,0})
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectMatrix = m_ProjectMatrix*m_ViewMatrix;
	}


	void OrthoCamera::SetProjectMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_ProjectMatrix= glm::ortho(left, right, bottom, top, zNear, zFar);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}

	void OrthoCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Position) * glm::rotate(glm::mat4(1.0f),glm::radians(m_angle),glm::vec3(0,0,1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}

	//////////////////////////////////////////////////////////////////////////////////
	/// PespectiveCamera ////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	PespectiveCamera::PespectiveCamera(float fov, float aspect, float zNear, float zFar)
		: m_ProjectMatrix(glm::perspective(fov,aspect, zNear, zFar)), m_angle(0), m_Position({ 0,0,0 })
	{
		RecalculateViewMatrix();
	}


	void PespectiveCamera::SetProjectMatrix(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectMatrix = glm::perspective(fov, aspect, zNear, zFar);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}

	void PespectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_angle), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}
}