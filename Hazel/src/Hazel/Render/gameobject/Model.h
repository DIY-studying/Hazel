#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "Hazel/Render/Buffer.h"

namespace Hazel {

	class Model
	{
	public:
		Model(const std::string& name, const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib);
		~Model();

		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; CalculateModelMatrix(); }
		inline const glm::vec3& GetPosition() { return m_Position; }
		inline void SetAngle(float angle) { m_Angle = angle; CalculateModelMatrix();  }
		inline const float& GetAngle() { return m_Angle; }

		inline const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		inline const Ref<VertexBuffer>& GetVertexBuffer() const { return m_Vb; }
		inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_Ib; }

		static std::vector<Ref<Model>> Creat(const std::string objPath);

	private:
		void CalculateModelMatrix();

	private:
		Ref<VertexBuffer> m_Vb;
		Ref<IndexBuffer> m_Ib;
		glm::vec3 m_Position;
		glm::mat4 m_ModelMatrix;

		std::string m_Name;
		float m_Angle;
	};
}

