#include "hzpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Hazel
{

	//////////////////////////////////////////////////////////////////////////////////
	/// VertexBuffer ///////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertexs, uint32_t size)
		:m_RenderID(0)
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertexs, GL_STATIC_DRAW);

	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_BufferLayout;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_BufferLayout = layout;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	//////////////////////////////////////////////////////////////////////////////////
	/// IndexBuffer ///////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexs, uint32_t count)
		:m_RenderID(0),m_Count(count)
	{
		glGenBuffers(1,&m_RenderID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*count, indexs, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}
	
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}