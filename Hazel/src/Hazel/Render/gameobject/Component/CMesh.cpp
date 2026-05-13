#include "hzpch.h"

#include "CMesh.h"
#include "Hazel/Render/Render.h"
#include "Component.h"

namespace  Hazel {
	CMesh::CMesh(const std::vector<Vertex>& vertexs, const std::vector<uint32_t>& indices)
	{
		this->vertexs = vertexs;
		this->indices = indices;
	}


	CMesh::CMesh(std::vector<Vertex>&& vertexs, std::vector<uint32_t>&& indices)
	{
		this->vertexs = std::move(vertexs);
		this->indices = std::move(indices);
	}
}