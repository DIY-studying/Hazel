#include "hzpch.h"
#include "Model.h"
#include "OBJ_Loader.h"
#include "Hazel/Render/Render.h"
#include "Hazel/Render/gameobject/Component/CMesh.h"

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
	
	static size_t ObjlVertexSize()
	{
		return sizeof(objl::Vertex);
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

			uint32_t size = (uint32_t)(mesh.Vertices.size() * ObjlVertexSize());
			std::vector<Vertex> vertices;
			vertices.reserve(mesh.Vertices.size());
			for (int i = 0;i < mesh.Vertices.size();i++)
			{
				vertices.push_back({ {mesh.Vertices[i].Position.X, mesh.Vertices[i].Position.Y, mesh.Vertices[i].Position.Z},
					{mesh.Vertices[i].Normal.X, mesh.Vertices[i].Normal.Y, mesh.Vertices[i].Normal.Z},
					{mesh.Vertices[i].TextureCoordinate.X, mesh.Vertices[i].TextureCoordinate.Y},
					{1.0f,1.0f,1.0f} });
			}
			model->AddComponent<CMesh>(reinterpret_cast<std::vector<Vertex>&&>(vertices), reinterpret_cast<std::vector<uint32_t>&&>(mesh.Indices));

			models.push_back(model);
		}

		return models;
	}

	Model::Model(const std::string& name)
		:GameObject(), m_Name(name)
	{

	}

	Model::~Model()
	{
	}

}