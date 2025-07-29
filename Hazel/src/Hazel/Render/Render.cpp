#include "hzpch.h"
#include "Render.h"
#include "RenderCommand.h"

namespace Hazel
{
	Render::SceneData* Render::m_SceneData=new Render::SceneData();
	void Render::BeginScene(OrthoCamera& orthoCamera)
	{
		m_SceneData->ViewProjectMatrix = orthoCamera.GetViewProjectMatrix();
	}

	void Render::EndScene()
	{

	}

	void Render::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		shader->Bind();

		shader->SetUniformMat4(m_SceneData->ViewProjectMatrix,"m_MVP");
		RenderCommand::DrawIndex(vertexArray);
	}

}