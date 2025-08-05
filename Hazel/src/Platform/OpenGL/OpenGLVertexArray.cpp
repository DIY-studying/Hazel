#include "hzpch.h"
#include "OpenGLVertexArray.h"

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
		glGenVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}


	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "vertexBuffer don't set layout.");

		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		unsigned int index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count, ShaderDataTypeToOpenGLType(element.Type), element.Normalize ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

	}

	

}

