#pragma once

#include "Hazel/Render/RenderAPI.h"

namespace Hazel {

	class  OpenGLRenderAPI: public RenderAPI
	{
	public:
		virtual void Init() override;

		virtual void DrawIndex(const Ref<VertexArray>& vertexArray) override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

	};
}