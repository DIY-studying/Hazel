#include "hzpch.h"
#include "Model.h"
#include "OBJ_Loader.h"
#include <glm/ext/matrix_transform.hpp>

namespace Hazel {

	struct VertexLayout
	{	
		glm::vec3 pos = {0,0,0};
		glm::vec3 norma = { 0,0,0 };
		glm::vec2 texCoords = { 0,0};

		static uint32_t Size()
		{
			return 3+3+2;
		}

		static BufferLayout GetLayout()
		{
			BufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			return layout;
		}
	};

	Model::Model(const std::string objPath)
		:m_Position(0)
	{
		objl::Loader loader;
		bool loadState = loader.LoadFile(objPath);
		loader.LoadFile("Assets/Model/bunny.obj");
		if (!loadState)
		{
			HZ_CORE_ASSERT(false, "Fail load file.");
			HZ_CORE_ERROR("'{0}' load file fialed.", objPath);
		}

		HZ_CORE_INFO("{0}", loader.LoadedMeshes.size());

		uint32_t size = (uint32_t)(loader.LoadedMeshes[0].Vertices.size() * VertexLayout::Size() * sizeof(float));

		m_Vb = VertexBuffer::Creat((float*)&loader.LoadedMeshes[0].Vertices[0], size);
		m_Vb->SetLayout(VertexLayout::GetLayout());
		m_Ib = IndexBuffer::Creat(&loader.LoadedMeshes[0].Indices[0], loader.LoadedMeshes[0].Indices.size());

		CalculateModelMatrix();
	}

	Model::~Model()
	{
	}

	void Model::CalculateModelMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f),m_Position);
		m_ModelMatrix = translate;
	}

}