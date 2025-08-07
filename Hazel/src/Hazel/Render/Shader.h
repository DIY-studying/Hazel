#pragma once

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

namespace Hazel
{
	class  Shader
	{
	public:
		virtual ~ Shader() = default;

		virtual void Bind() const = 0 ;
		virtual void UnBind() const = 0;

	public:
		static Ref<Shader> Creat(const std::string& filePath);
		static Ref<Shader> Creat(const std::string& vertexSrc, const std::string fragmentSrc);

	};
}