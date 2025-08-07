#pragma once

#include <cstdint>
#include <vector>

namespace Hazel
{
	enum class ShaderDataType
	{
		None = 0, Float,Int
	};
	template <typename T>
	static ShaderDataType TypeToShaderDataType()
	{
		return ShaderDataType::None;
	}
	template<>
	static ShaderDataType TypeToShaderDataType<float>()
	{
		return ShaderDataType::Float;
	}
	template<>
	static ShaderDataType TypeToShaderDataType<int>()
	{
		return ShaderDataType::Int;
	}
	// when modify ShaderDataType, you need also modify function below.
	static unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct BufferElement
	{
		unsigned int Offset;
		bool Normalize;
		unsigned int Count;
		ShaderDataType Type;

		BufferElement( bool normalize,unsigned int count, unsigned int offset, ShaderDataType type)
			:Count(count),Normalize(normalize),Offset(offset), Type(type)
		{

		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() :m_stride(0) {}

		template <typename T> void Push(unsigned int  count, bool normalize = false)
		{
			switch (TypeToShaderDataType<T>())
			{
			case ShaderDataType::Float:
				m_Elements.push_back(BufferElement(normalize, count, m_stride, ShaderDataType::Float));
				m_stride += sizeof(float) * count;
				break;
			case ShaderDataType::Int:
				m_Elements.push_back(BufferElement(normalize, count, m_stride, ShaderDataType::Int));
				m_stride += sizeof(int) * count;
				break;
			case ShaderDataType::None:
				HZ_CORE_ASSERT(false, "Unknow type!");
				break;
			}
		}

		inline uint32_t GetStride() const { return m_stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_stride;
	};

	class  VertexBuffer
	{
	public:


		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Creat(float* vertexs, uint32_t size);
	};

	class IndexBuffer
	{
	public:

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() = 0;

		static Ref<IndexBuffer> Creat(uint32_t* indexs, uint32_t count);
	};
}