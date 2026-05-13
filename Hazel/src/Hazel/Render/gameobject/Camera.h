#pragma once
#include "Hazel/Render/gameobject/GameObject.h"


namespace Hazel {

	class Camera :public GameObject
	{
	public:
		virtual const Eigen::Matrix4f& GetViewProjectMatrix()
		{
			m_ViewProjectMatrix = m_ProjectMatrix * GetViewMatrix();
			return m_ViewProjectMatrix; 
		};
		virtual const Eigen::Matrix4f& GetProjectMatrix()const { return m_ProjectMatrix; };
		virtual const Eigen::Matrix4f& GetViewMatrix() 
		{
			Eigen::Matrix4f transform = GetTranslateMatrix()* GetRotationMatrix();
			m_ViewMatrix = transform.inverse();
			return m_ViewMatrix;
		};
	protected:
		Camera(const Eigen::Vector3f& pos) : GameObject() ,m_ProjectMatrix(){};
	protected:
		Eigen::Matrix4f m_ProjectMatrix;
		Eigen::Matrix4f m_ViewMatrix;
		Eigen::Matrix4f m_ViewProjectMatrix;
	};

	class OrthoCamera: public Camera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		void SetProjectMatrix(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);
	};

	class PespectiveCamera : public Camera
	{
	public:
		PespectiveCamera(float fov, float aspect, float zNear = 0.1f, float zFar = 100.0f);

		virtual void Submit(const Ref<Shader>& shader) override;

		void SetProjectMatrix(float fov, float aspect, float zNear = 0.1f, float zFar = 1000.0f);

	};
}