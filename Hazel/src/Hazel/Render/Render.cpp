#include "hzpch.h"
#include "Render.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Render/gameobject/3D/Model.h"
#include "gameobject/Component/Mesh.h"


namespace Hazel
{
	
	
	static Ref<Shader> m_shader;
	static Ref<VertexBuffer> m_vb;
	static Ref<VertexArray> m_VertexArray;
	static Ref<IndexBuffer> m_ib;
	static uint32_t count = 0;
	static uint32_t total_count = BATCH_TRIANGLE_COUNT * 3;
	static std::vector<Vertex> vertexs;
	static std::vector<uint32_t> indices;


	Ref<SceneData> Render::m_SceneData=make_Ref<SceneData>();
	void Render::BeginScene(const Ref<Camera>& camera, const Ref<Shader>& shader)
	{
		m_SceneData->viewMatrix = camera->GetViewMatrix();
		m_SceneData->projectMatrix = camera->GetProjectMatrix();
		m_shader = shader;
		m_vb =VertexBuffer::Creat( total_count*sizeof(Vertex));
		m_ib = IndexBuffer::Creat(total_count);
		vertexs.reserve(total_count);
		indices.reserve(total_count);

		m_vb->SetLayout(Vertex::Layout());
		m_VertexArray = VertexArray::Creat();
		m_VertexArray->SetVertexBuffer(m_vb);
		m_VertexArray->SetIndexBuffer(m_ib);
	}

	void Render::Flush()
	{
		if (count == 0)
			return;
		m_vb->SetData(&vertexs[0],vertexs.size()*sizeof(Vertex));
		m_ib->SetData(&indices[0], indices.size());
		RenderCommand::DrawIndex(m_VertexArray);
		vertexs.clear();
		indices.clear();
		count = 0;

	}

	void Render::Init()
	{
		RenderCommand::Init();
	}

	Ref<SceneData> Render::GetSceneData()
	{
		return m_SceneData;
	}

	void Render::EndScene()
	{
		//camera
		m_shader->SetMat4("u_ProjectMatrix", m_SceneData->projectMatrix);
		m_shader->SetMat4("u_ViewMatrix", m_SceneData->viewMatrix);

		m_VertexArray->Bind();
		m_shader->Bind();
		
		for (auto mesh : m_SceneData->meshs)
		{
			for (size_t i = 0; i < mesh->Indices.size(); i++)
			{
				int index = mesh->Indices[i];
				
				if (count >= total_count)
				{
					Flush();
				}

				count++;
				vertexs.push_back(mesh->vertexs[index]);
				indices.push_back(vertexs.size()-1);
			}
		}
		
		Flush();
	}

	void Render::Submit(const std::vector<Ref<GameObject>>& gameObjes)
	{
		m_VertexArray->Bind();
		m_shader->Bind();

		for (auto gameObj : gameObjes)
		{
			gameObj->Submit(m_shader);
		}
	}

}