#pragma once

#include "Hazel/Render/VertexArray.h"

namespace Hazel {
	class OpenGLVertexArray: public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const Ref<VertexBuffer>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		unsigned int m_RenderID;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<VertexBuffer> m_VertexBuffers;
	};
}
