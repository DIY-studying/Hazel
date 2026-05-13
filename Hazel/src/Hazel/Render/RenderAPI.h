#pragma once

#include "VertexArray.h"

namespace Hazel {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};
		
		virtual void Init() = 0;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndex(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawArray(const Ref<VertexArray>& vertexArray,uint32_t first,uint32_t count) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const Eigen::Vector4f& color ) = 0;



		inline static API GetAPI() { return m_API; }
	private:
		static API m_API;
	};
}
