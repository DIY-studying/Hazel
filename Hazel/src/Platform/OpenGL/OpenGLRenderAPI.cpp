#include "hzpch.h"
#include "OpenGLRenderAPI.h"
#include "glad/glad.h"
#include "OpenGLError.h"

namespace Hazel
{
	void OpenGLRenderAPI::Init()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void OpenGLRenderAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		GLCall(glViewport(0,0,width,height));
	}

	void OpenGLRenderAPI::DrawIndex(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		GLCall(glDrawElements(GL_TRIANGLES,vertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT,nullptr));
	}

	void OpenGLRenderAPI::DrawArray(const Ref<VertexArray>& VertexArray, uint32_t first, uint32_t count)
	{
		VertexArray->Bind();
		GLCall(glDrawArrays(GL_TRIANGLES,first, count));
	}


	void OpenGLRenderAPI::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderAPI::SetClearColor(const Eigen::Vector4f& color)
	{
		GLCall(glClearColor(color.x(),color.y(), color.z(), color.w()));
	}
}