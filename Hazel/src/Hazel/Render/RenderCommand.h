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

		inline static void  DrawIndex(const Ref<VertexArray>& vertexArray)
		{
			m_RenderAPI->DrawIndex(vertexArray);
		}
		inline static void SetClearColor(const glm::vec4 color)
		{
			m_RenderAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			m_RenderAPI->Clear();
		}
	private:
			static RenderAPI* m_RenderAPI;
	};
}