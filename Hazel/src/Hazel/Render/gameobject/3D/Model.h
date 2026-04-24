#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/gameobject/GameObject.h"
#include "Hazel/Render/gameobject/Component/Mesh.h"

namespace Hazel {

	class Model : public GameObject
	{
	public:
		Model(const std::string& name);
		~Model();

		inline void SetPosition(const glm::vec3& pos) { m_pos = pos;  }
		inline const glm::vec3& GetPosition() { return m_pos; }
		inline void SetAngle(float angle) { m_Angle = angle;  }
		inline  float GetAngle() { return m_Angle; }

		inline const glm::mat4& GetModelMatrix()  { CalculateModelMatrix(); return m_ModelMatrix; }

		// componet future
		inline  Ref<Mesh> GetMesh()  { return m_mesh; }
		
		bool AddMesh();


		static std::vector<Ref<Model>> Creat(const std::string objPath);

	private:
		void CalculateModelMatrix();

	private:
		Ref<Mesh> m_mesh;
		glm::mat4 m_ModelMatrix;


		std::string m_Name;
		float m_Angle;
	};
}

