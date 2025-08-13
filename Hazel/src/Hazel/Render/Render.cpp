#include "hzpch.h"
#include "Render.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Render/gameobject/Model.h"

namespace Hazel
{
	Render::SceneData* Render::m_SceneData=new Render::SceneData();
	void Render::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectMatrix = camera.GetViewProjectMatrix();
	}

	void Render::Init()
	{
		RenderCommand::Init();
	}

	void Render::EndScene()
	{

	}

	void Render::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->SetMat4( "u_ViewProject", m_SceneData->ViewProjectMatrix);

		
		RenderCommand::DrawIndex(vertexArray);
	}

}