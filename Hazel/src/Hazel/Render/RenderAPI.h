#pragma once

#include "VertexArray.h"
#include <glm/ext/vector_float4.hpp>

namespace Hazel {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};
		
		virtual void Init() = 0;

		virtual void DrawIndex(const Ref<VertexArray>& vertexArray) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color ) = 0;

		inline static API GetAPI() { return m_API; }
	private:
		static API m_API;
	};
}
