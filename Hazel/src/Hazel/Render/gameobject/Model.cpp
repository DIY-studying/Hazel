#include "hzpch.h"
#include "Model.h"
#include "OBJ_Loader.h"
#include <glm/ext/matrix_transform.hpp>

namespace Hazel {

	// objl::vertex similar struct 
	struct VertexLayout
	{	
		glm::vec3 pos = {0,0,0};
		glm::vec3 norma = { 0,0,0 };
		glm::vec2 texCoords = { 0,0};

		static uint32_t Size()
		{
			return (3+3+2) * sizeof(float);
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

	std::vector<Ref<Model>> Model::Creat(const std::string objPath)
	{

		objl::Loader loader;
		bool loadState = loader.LoadFile(objPath);
		HZ_CORE_ASSERT(loadState, "Fail load file.");
		if (!loadState)
			HZ_CORE_ERROR("'{0}' load file fialed.", objPath);

		std::vector<Ref<Model>> models;

		for (auto& mesh : loader.LoadedMeshes)
		{
			uint32_t size = (uint32_t)(mesh.Vertices.size() * VertexLayout::Size());
			Ref<VertexBuffer> vb = VertexBuffer::Creat((float*)&mesh.Vertices[0], size);
			vb->SetLayout(VertexLayout::GetLayout());
			Ref<IndexBuffer> ib = IndexBuffer::Creat(&mesh.Indices[0], (uint32_t)mesh.Indices.size());

			Ref<Model> model = make_Ref<Model>(mesh.MeshName,vb,ib);
			models.push_back(model);
		}

		return models;
	}

	Model::Model(const std::string& name, const Ref<VertexBuffer>& vb, const Ref<IndexBuffer>& ib)
		:m_Position(0),m_Name(name),m_Vb(vb),m_Ib(ib),m_Angle(0)
	{
		CalculateModelMatrix();

	}

	Model::~Model()
	{
	}

	void Model::CalculateModelMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rotate=glm::rotate(glm::mat4(1.0f),m_Angle,glm::vec3(0,1,0));
		glm::mat4 scale = glm::mat4(1.0f);
		m_ModelMatrix = scale*translate* rotate;
	}

}