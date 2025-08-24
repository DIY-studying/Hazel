#include "hzpch.h"
#include "Render.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Render/gameobject/Model.h"


namespace Hazel
{
	Render::SceneData* Render::m_SceneData=new Render::SceneData();
	void Render::BeginScene(const Camera& camera)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectMatrix = camera.GetProjectMatrix();
	}

	void Render::BeginScene(const Camera& camera, const Light& light)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectMatrix = camera.GetProjectMatrix();

		m_SceneData->light_Pos = light.GetPos();
		m_SceneData->light_ka = light.GetKa();
		m_SceneData->light_kd = light.GetKd();
		m_SceneData->light_ks = light.GetKs();
		m_SceneData->light_Intensity = light.GetLightIntensity();
		m_SceneData->light_amb_Intensity = light.GetAmbLightIntensity();
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

		//camera
		shader->SetMat4( "u_ProjectMatrix", m_SceneData->ProjectMatrix);
		shader->SetMat4("u_ViewMatrix", m_SceneData->ViewMatrix);
		shader->SetFloat3("u_viewPos", m_SceneData->view_pos);

		//light
		shader->SetFloat3("u_light_pos",m_SceneData->light_Pos);
		shader->SetFloat3("u_light_ka", m_SceneData->light_ka);
		shader->SetFloat3("u_light_kd", m_SceneData->light_kd);
		shader->SetFloat3("u_light_ks", m_SceneData->light_ks);
		shader->SetFloat3("u_light_Instensity", m_SceneData->light_Intensity);
		shader->SetFloat3("u_light_amb_instensity", m_SceneData->light_amb_Intensity);


		
		RenderCommand::DrawIndex(vertexArray);
	}

}