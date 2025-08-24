#pragma once
#include "Hazel/Render/Shader.h"
#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include "glad/glad.h"

namespace Hazel
{
	class  OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name,const std::string& vertexSrc, const std::string fragmentSrc);
		~OpenGLShader();

		// Shader class Interface
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual const std::string& GetName() const override;

		virtual void SetMat4(const std::string& name, const glm::mat4& mat) override { SetUniformMat4(mat,name); }
		virtual void SetFloat3(const std::string& name, const glm::vec3& mat) override { SetUniformFloat3(mat,name); };
		virtual void SetInt1(const std::string& name, int slot) override { SetUniformInt1(slot,name); }
		//////////////////////////////////////////////////////////////////////////////////////

		
	private:
		void SetUniformMat4(const glm::mat4& matrix, const std::string& name);
		void SetUniformMat3(const glm::mat3& matrix, const std::string& name);
		void SetUniformFloat3(const glm::vec3& vector, const std::string& name);
		void SetUniformFloat4(const glm::vec4& vector, const std::string& name);
		void SetUniformInt1(int slot, const std::string& name);

		GLint GetLocation(GLuint renderID ,const std::string& name);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcMap);
		std::unordered_map<GLenum,std::string> Process(const std::string& source);
		std::string ReadFile(const std::string & filePath);
	private:
		uint32_t m_RenderID;
		std::string m_name;

	};
}
