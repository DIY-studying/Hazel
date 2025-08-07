#include "hzpch.h"


#include "Buffer.h"
#include "Render.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	Ref<VertexBuffer> VertexBuffer::Creat(float* vertexs, uint32_t size)
	{
		switch (Render::GetAPI())
		{
		case RenderAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported. "); return nullptr;
		case RenderAPI::API::OpenGL: return make_Ref<OpenGLVertexBuffer>(vertexs,size) ;
		}


		HZ_CORE_ASSERT(false, "Unknow RenderAPI. ");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Creat(uint32_t* indexs, uint32_t count)
	{
		switch (Render::GetAPI())
		{
		case RenderAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported. "); return nullptr;
		case RenderAPI::API::OpenGL: return make_Ref<OpenGLIndexBuffer>(indexs, count);
		}


		HZ_CORE_ASSERT(false, "Unknow RenderAPI. ");
		return nullptr;
	}
}