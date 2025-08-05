#pragma once

#include "Hazel/Render/Shader.h"

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

namespace Hazel
{
	class  OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void SetUniformMat4(const glm::mat4& matrix, const std::string& name);
		void SetUniformMat3(const glm::mat3& matrix, const std::string& name);
		void SetUniformFloat3(const glm::vec3& vector, const std::string& name);
		void SetUniformFloat4(const glm::vec4& vector, const std::string& name);
		void SetUniformInt1(int slot, const std::string& name);
	private:
		uint32_t m_RenderID;

	};
}
