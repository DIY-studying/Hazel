#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLError.h"
#include "glad/glad.h"
#include "Hazel/Render/Buffer.h"

namespace Hazel
{
	unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case Hazel::ShaderDataType::Float: return GL_FLOAT;
			case Hazel::ShaderDataType::Int: return GL_INT;
		}

		HZ_CORE_ASSERT(false, "Unknow type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{	
		GLCall(glGenVertexArrays(1, &m_RenderID));
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RenderID));
	}

	void OpenGLVertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RenderID));
	}


	void OpenGLVertexArray::UnBind() const
	{
		GLCall(glBindVertexArray(0));
	}

	void OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "vertexBuffer don't set layout.");


		Bind();
		vertexBuffer->Bind();

		unsigned int index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(index, element.Count, ShaderDataTypeToOpenGLType(element.Type), element.Normalize ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)(uintptr_t)element.Offset));
			index++;
		}

		m_VertexBuffers = vertexBuffer;
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

	}

	

}

