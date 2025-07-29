#pragma once

#include "Hazel/Render/RenderAPI.h"

namespace Hazel {

	class  OpenGLRenderAPI: public RenderAPI
	{
	public:

		virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

	};
}