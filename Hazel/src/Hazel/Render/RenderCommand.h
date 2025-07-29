#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"


namespace Hazel {
	class RenderCommand
	{
	public:
		inline static void  DrawIndex(const std::shared_ptr<VertexArray>& vertexArray)
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