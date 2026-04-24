#include "hzpch.h"
#include "Model.h"
#include "OBJ_Loader.h"
#include <glm/ext/matrix_transform.hpp>
#include <Hazel/Render/gameobject/Component/Mesh.h>
#include "Hazel/Render/Render.h"

namespace Hazel {

	// Objl::Vertex data layout
	static BufferLayout OBJLVertexLayout()
	{
		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		return layout;
	}



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
			Ref<Model> model = make_Ref<Model>(mesh.MeshName);
			model->AddMesh();
			Ref<Mesh> model_mesh = model->GetMesh();

			uint32_t size = (uint32_t)(mesh.Vertices.size() * sizeof(objl::Vertex));
			model_mesh->vertexs = reinterpret_cast<std::vector<Vertex>&&>(mesh.Vertices);
			model_mesh->Indices = reinterpret_cast<std::vector<uint32_t>&&>(mesh.Indices);

			models.push_back(model);
		}

		return models;
	}

	bool Model::AddMesh()
	{
		if (m_mesh)
			return false;
		m_mesh = make_Ref<Mesh>();
		Render::GetSceneData()->meshs.push_back(m_mesh);
		return true;
	}

	Model::Model(const std::string& name)
		:GameObject(glm::vec3()), m_Name(name), m_Angle(0)
	{
		m_ModelMatrix = glm::mat4();
	}

	Model::~Model()
	{
	}

	void Model::CalculateModelMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_pos);
		glm::mat4 rotate=glm::rotate(glm::mat4(1.0f),m_Angle,glm::vec3(0,1,0));
		glm::mat4 scale = glm::mat4(1.0f);
		m_ModelMatrix = scale*translate* rotate;
	}

}