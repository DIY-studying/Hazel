#pragma once
#include <glm/ext/matrix_float4x4.hpp>

namespace Hazel {

	class Camera
	{
	public:
		virtual const glm::mat4& GetViewProjectMatrix() const = 0;
		virtual const glm::vec3& GetPosition()  const = 0;
		virtual const glm::mat4& GetProjectMatrix()const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
	};

	class OrthoCamera: public Camera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		virtual const glm::vec3& GetPosition() const override  { return m_Position; }
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalculateViewMatrix(); }
		inline void SetRotation(float angle) { m_angle = angle; RecalculateViewMatrix(); }

		virtual const glm::mat4& GetViewProjectMatrix() const override { return m_ViewProjectMatrix; }
		virtual const glm::mat4& GetProjectMatrix() const override { return m_ProjectMatrix; }
		virtual const glm::mat4& GetViewMatrix()  const override { return m_ViewMatrix; }

		void SetProjectMatrix(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectMatrix;

		glm::vec3 m_Position;
		float m_angle;
	};

	class PespectiveCamera : public Camera
	{
	public:
		PespectiveCamera(float fov, float aspect, float zNear = 0.1f, float zFar = 100.0f);

		virtual const glm::vec3& GetPosition() const override { return m_Position; }
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalculateViewMatrix(); }
		inline void SetRotation(float angle) { m_angle = angle; RecalculateViewMatrix(); }

		virtual const glm::mat4& GetViewProjectMatrix() const override { return m_ViewProjectMatrix; }
		virtual const glm::mat4& GetProjectMatrix()const override { return m_ProjectMatrix; }
		virtual const glm::mat4& GetViewMatrix()const override { return m_ViewMatrix; }

		void SetProjectMatrix(float fov, float aspect, float zNear = 0.1f, float zFar = 1000.0f);

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