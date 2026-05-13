#include "hzpch.h"
#include "Camera.h"


namespace Hazel
{
	//////////////////////////////////////////////////////////////////////////////////
	/// OrthoCamera //////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: Camera(Eigen::Vector3f())
	{
		SetProjectMatrix(left, right, bottom, top, zNear, zFar);
	}


	void OrthoCamera::SetProjectMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		
		Eigen::Matrix4f ortho_mat = Eigen::Matrix4f::Identity();

		ortho_mat(0, 0) = 2.0f / (right - left);
		ortho_mat(1, 1) = 2.0f / (top - bottom);
		ortho_mat(2, 2) = -2.0f / (zFar - zNear);
		ortho_mat(0, 3) = -(right + left) / (right - left);
		ortho_mat(1, 3) = -(top + bottom) / (top - bottom);
		ortho_mat(2, 3) = -(zFar + zNear) / (zFar - zNear);

		m_ProjectMatrix = ortho_mat;
	}

	//////////////////////////////////////////////////////////////////////////////////
	/// PespectiveCamera ////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	PespectiveCamera::PespectiveCamera(float fov, float aspect, float zNear, float zFar)
		:Camera(Eigen::Vector3f())
	{

		SetProjectMatrix(fov, aspect, zNear, zFar);
	}

	void PespectiveCamera::Submit(const Ref<Shader>& shader)
	{
		shader->SetFloat3("u_viewPos", GetPos());
	}

	void PespectiveCamera::SetProjectMatrix(float fov, float aspect, float zNear, float zFar)
	{
		Eigen::Matrix4f proj_mat = Eigen::Matrix4f::Identity();
		float fov_rad = fov * PI / 180.0f;
		float tan_half_fov = std::tan(fov_rad * 0.5f);

		proj_mat(0, 0) = 1.0f / (aspect * tan_half_fov);
		proj_mat(1, 1) = 1.0f / tan_half_fov;
		proj_mat(2, 2) = -(zNear + zFar) / (zFar - zNear);
		proj_mat(2, 3) = -2.0f * zNear * zFar / (zFar - zNear);
		proj_mat(3, 2) = -1.0f;
		proj_mat(3, 3) = 0.0f;
		m_ProjectMatrix = proj_mat;
	}
}