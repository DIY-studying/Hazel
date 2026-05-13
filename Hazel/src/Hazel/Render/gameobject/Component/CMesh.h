#pragma once

#include "hzpch.h"

#include "Hazel/Render/Buffer.h"
#include "Hazel/Core.h"
#include "Component.h"

namespace Hazel {

	struct Vertex
	{
		Eigen::Vector3f pos;
		Eigen::Vector3f normal;
		Eigen::Vector2f texCoords;
		Eigen::Vector3f color;

		static BufferLayout Layout()
		{
			BufferLayout layout = BufferLayout();
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			layout.Push<float>(3);
			return layout;
		}

	};

	class Render;

	class CMesh :public Component
	{

	public:
		std::vector<Vertex> vertexs;
		std::vector<uint32_t> indices;

		
	public:
		CMesh(const std::vector<Vertex>& vertexs, const std::vector<uint32_t>& indices);
		CMesh(std::vector<Vertex>&& vertexs, std::vector<uint32_t>&& indices);
		CMesh() = default;

	public:
		static BufferLayout Layout()
		{
			return Vertex::Layout();
		}
	};
	
}