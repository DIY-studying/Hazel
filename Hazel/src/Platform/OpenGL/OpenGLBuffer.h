#pragma once
#include "Hazel/Render/Buffer.h"
#include <cstdint>

namespace Hazel
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertexs, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind()  const override;

		virtual const BufferLayout& GetLayout() const override;
		virtual void SetLayout(const BufferLayout& layout) override;

	private:
		BufferLayout m_BufferLayout;
		uint32_t m_RenderID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indexs, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline virtual uint32_t GetCount() { return m_Count; }
	private:
		uint32_t m_RenderID, m_Count;
	};
}
