#include "hzpch.h"
#include "OpenGLRenderAPI.h"
#include "glad/glad.h"


namespace Hazel
{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(0,0,width,height);
	}

	void OpenGLRenderAPI::DrawIndex(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES,vertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT,nullptr);
	}

	void OpenGLRenderAPI::DrawArray(const Ref<VertexArray>& VertexArray, uint32_t first, uint32_t count)
	{
		VertexArray->Bind();
		glDrawArrays(GL_TRIANGLES,first, count);
	}


	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r,color.g, color.b, color.w);
	}
}