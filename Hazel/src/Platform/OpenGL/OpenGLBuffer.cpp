#include "hzpch.h"
#include "OpenGLBuffer.h"
#include "OpenGLError.h"
#include "glad/glad.h"

namespace Hazel
{

	//////////////////////////////////////////////////////////////////////////////////
	/// VertexBuffer ///////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer( uint32_t size)
		:m_RenderID(0)
	{
		GLCall(glGenBuffers(1, &m_RenderID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));

	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertexs, uint32_t size)
		:m_RenderID(0)
	{
		GLCall(glGenBuffers(1, &m_RenderID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertexs, GL_STATIC_DRAW));

	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size)
	{
		Bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER,0, size ,data));
	}

	void OpenGLVertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
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
		GLCall(glDeleteBuffers(1, &m_RenderID));
	}


	//////////////////////////////////////////////////////////////////////////////////
	/// IndexBuffer ///////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer( uint32_t count)
		:m_RenderID(0), m_Count(count)
	{
		GLCall(glGenBuffers(1, &m_RenderID));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, nullptr, GL_DYNAMIC_DRAW));
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexs, uint32_t count)
		:m_RenderID(0),m_Count(count)
	{
		GLCall(glGenBuffers(1,&m_RenderID));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*count, indexs, GL_STATIC_DRAW));
	}

	void OpenGLIndexBuffer::SetData(void* data, uint32_t count)
	{
		Bind();
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * count, data));
	}


	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RenderID));
	}
	
	void OpenGLIndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}