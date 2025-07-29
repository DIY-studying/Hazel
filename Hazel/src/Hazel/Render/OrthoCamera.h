#pragma once
#include <glm/ext/matrix_float4x4.hpp>



namespace Hazel {

	class OrthoCamera
	{
	public:
		OrthoCamera(float left,float right,float bottom,float top, float zNear=-1.0f, float zFar=1.0f);

		const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3&  pos) {m_Position = pos; RecalculateViewMatrix();}
		inline void SetRotation(float angle) { m_angle = angle; RecalculateViewMatrix(); }
		
		inline const glm::mat4& GetViewProjectMatrix() { return m_ViewProjectMatrix; }
		inline const glm::mat4& GetProjectMatrix() { return m_ProjectMatrix; }
		inline const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }


	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectMatrix;

		glm::vec3 m_Position;
		float m_angle;


	};
}