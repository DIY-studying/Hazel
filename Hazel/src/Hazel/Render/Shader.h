#pragma once

#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include <unordered_map>

namespace Hazel
{
	class  Shader
	{
	public:
		virtual ~ Shader() = default;

		virtual void Bind() const = 0 ;
		virtual void UnBind() const = 0;
		virtual const std::string& GetName() const = 0;

	public:
		static Ref<Shader> Creat(const std::string& filePath);
		static Ref<Shader> Creat(const std::string& name,const std::string& vertexSrc, const std::string fragmentSrc);

	};

	class  ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name,const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		bool Exist(const std::string& name);

		Ref<Shader> Get(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}