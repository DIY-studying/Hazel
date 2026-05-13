#pragma once

#include <Hazel/Render/gameobject/Component/CMesh.h>
#include <Hazel/Render/gameobject/GameObject.h>


namespace Hazel
{
	class Cube:public GameObject
	{
	public:
		inline Cube():GameObject() {
			AddComponent<CMesh>();
			GenerateMesh();
		}
	private:
		void GenerateMesh();

	private:
		int m_resolution = 2;	// point per row
		float m_size = 1.0f;	// edge length
		Eigen::Vector3f m_color = Eigen::Vector3f(1.0f, 1.0f, 1.0f);
	};
}
