#include "hzpch.h"
#include "Shader.h"

#include "Render.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Creat(const std::string& vertexSrc, const std::string fragmentSrc)
	{
		switch (Render::GetAPI())
		{
		case RenderAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported. "); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}


		HZ_CORE_ASSERT(false, "Unknow RenderAPI. ");
		return nullptr;
	}
}