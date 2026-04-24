#pragma once

#include "hzpch.h"

#include "Hazel/Render/Buffer.h"


namespace Hazel {

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 norma ;
		glm::vec2 texCoords;

		static BufferLayout Layout()
		{
			BufferLayout layout=BufferLayout();
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			return layout;
		}

	};

	struct Mesh
	{
		std::vector<Vertex> vertexs;
		std::vector<uint32_t> Indices;

		static BufferLayout Layout()
		{
			return Vertex::Layout();
		}

		Mesh() {};
	}; 
	
}