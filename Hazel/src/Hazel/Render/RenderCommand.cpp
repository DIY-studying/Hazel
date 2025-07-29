#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Hazel {
	RenderAPI* RenderCommand::m_RenderAPI=new OpenGLRenderAPI();
}