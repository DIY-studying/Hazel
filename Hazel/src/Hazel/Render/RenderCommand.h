#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"


namespace Hazel {
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			m_RenderAPI->Init();
		}

		inline static void SetViewPort(uint32_t x,uint32_t y,uint32_t width, uint32_t height)
		{
			m_RenderAPI->SetViewPort(x,y,width,height);
		}

		inline static void  DrawIndex(const Ref<VertexArray>& vertexArray)
		{
			m_RenderAPI->DrawIndex(vertexArray);
		}

		inline static void  DrawArray(const Ref<VertexArray>& vertexArray, uint32_t first, uint32_t count)
		{
			m_RenderAPI->DrawArray(vertexArray,first,count);
		}

		inline static void SetClearColor(const glm::vec4 color)
		{
			m_RenderAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			m_RenderAPI->Clear();
		}
		inline static RenderAPI::API GetAPI() { return m_RenderAPI->GetAPI(); }
	private:
			static RenderAPI* m_RenderAPI;
	};
}