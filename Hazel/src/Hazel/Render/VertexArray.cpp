#include "hzpch.h"
#include"VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Render/Render.h"


namespace Hazel
{
	VertexArray* VertexArray::Creat()
	{
		switch (Render::GetAPI())
		{
		case RenderAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported. "); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLVertexArray();
		}


		HZ_CORE_ASSERT(false, "Unknow RenderAPI. ");
		return nullptr;
	}
}