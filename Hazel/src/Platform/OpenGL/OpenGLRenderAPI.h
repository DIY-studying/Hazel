#pragma once

#include "Hazel/Render/RenderAPI.h"

namespace Hazel {

	class  OpenGLRenderAPI: public RenderAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndex(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawArray(const Ref<VertexArray>& vertexArray, uint32_t first, uint32_t count) override;

		virtual void Clear() override;
		virtual void SetClearColor(const Eigen::Vector4f& color) override;

	};
}