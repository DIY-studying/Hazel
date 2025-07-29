#pragma once

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

namespace Hazel
{
	class  Shader
	{
	public:
		 Shader(const std::string& vertexSrc,const std::string fragmentSrc);
		~ Shader();

		void Bind();
		void UnBind();

		void SetUniformMat4(const glm::mat4& matrix, const std::string& name);

	private:
		uint32_t m_RenderID;

	};
}