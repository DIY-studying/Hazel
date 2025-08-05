#include "hzpch.h"
#include "Render.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Render::SceneData* Render::m_SceneData=new Render::SceneData();
	void Render::BeginScene(OrthoCamera& orthoCamera)
	{
		m_SceneData->ViewProjectMatrix = orthoCamera.GetViewProjectMatrix();
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
		dynamic_cast<OpenGLShader*>(shader.get())->SetUniformMat4(m_SceneData->ViewProjectMatrix, "u_ViewProject");;
		
		RenderCommand::DrawIndex(vertexArray);
	}

}