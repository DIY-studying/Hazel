#include "hzpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"
#include "Hazel/Render/Render.h"

namespace Hazel {
	Ref<Texture2D> Texture2D::Creat(const std::string& path)
	{
		switch (Render::GetAPI())
		{
		case RenderAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported. "); return nullptr;
		case RenderAPI::API::OpenGL: return make_Ref<OpenGLTexture2D>(path);
		}


		HZ_CORE_ASSERT(false, "Unknow RenderAPI. ");
		return nullptr;
	}
}