#include "hzpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Hazel
{
	static GLenum ShaderTypeFromString(const std::string& token)
	{
		if (token == "vertex")
			return GL_VERTEX_SHADER;
		else if (token == "fragment")
			return GL_FRAGMENT_SHADER;

		HZ_CORE_ERROR("'{0}' not support shader token.",token);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string& src = ReadFile(filePath);
		const std::unordered_map<GLenum,std::string>& shaderSrcMap = Process(src);
		Compile(shaderSrcMap);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> shaderSrcMap;
		shaderSrcMap[GL_VERTEX_SHADER] = vertexSrc;
		shaderSrcMap[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSrcMap);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
	


	void OpenGLShader::SetUniformMat4(const glm::mat4& matrix, const std::string& name)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::SetUniformMat3(const glm::mat3& matrix, const std::string& name)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformFloat3(const glm::vec3& vector, const std::string& name)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(vector));
	}
	void OpenGLShader::SetUniformFloat4(const glm::vec4& vector, const std::string& name)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}
	void OpenGLShader::SetUniformInt1(int slot, const std::string& name)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		glUniform1i(location,slot);
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcMap)
	{
		GLuint program = glCreateProgram();
		std::vector<GLuint> shaderIDs;
		for (auto& key : shaderSrcMap)
		{
			GLenum shaderType = key.first;
			const std::string& src = key.second;

			GLuint shader = glCreateShader(shaderType);
			shaderIDs.push_back(shader);

			const GLchar* source = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				HZ_CORE_ERROR("{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "shader complition fail.");
				return;
			}

			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : shaderIDs)
			{
				glDeleteShader(id);
			}
		
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "shader link fail.");
			return;
		}

		m_RenderID = program;
		for (auto id : shaderIDs)
		{
			glDeleteShader(id);
		}
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::Process(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSrcMap;
		const char* typeToken = "#type";
		size_t typeLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while(pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n",pos);
			HZ_CORE_ASSERT(eol != std::string::npos, "Unknow end of line.!");
			size_t begin = pos + 1 + typeLength;
			std::string type = source.substr(begin,eol- begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type),"Unknow token!");

			size_t nextline = source.find_first_not_of("\r\n", eol);
			HZ_CORE_ASSERT(nextline != std::string::npos, "Unknow end of line.!");

			pos = source.find(typeToken, nextline);
			shaderSrcMap[ShaderTypeFromString(type)] = source.substr(nextline,pos-nextline);
		}

		return shaderSrcMap;
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string source;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			source.resize(in.tellg());
			in.seekg(0,std::ios::beg);
			in.read(&source[0],source.size());
			in.close();
		}
		else
		{
			HZ_CORE_ERROR("Filepath '{0}' open fialed!",filePath);
			HZ_CORE_ASSERT(false,"Faile open file.");
		}
		return source;
	}
}