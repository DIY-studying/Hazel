#include <Hazel.h>
#include "Hazel/Core.h"
#include "Hazel/Render/gameobject/Model.h"

#include "imgui/imgui.h"

#include "string.h"

class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), fov(15),m_PerspectiveCamera(fov,1280/720),m_CamPosition(0,0,10),
		m_ModelAngle(0), m_ModelPos(0), m_light(m_LightPos),m_LightPos(0)
	{

		m_VertexArray = Hazel::VertexArray::Creat();

		std::vector<Hazel::Ref<Hazel::Model>> models = Hazel::Model::Creat("Assets/Model/spot_quadrangulated.obj");

		m_Model = models[0];

		m_VertexArray->AddVertexBuffer(m_Model->GetVertexBuffer());
		m_VertexArray->SetIndexBuffer(m_Model->GetIndexBuffer());

		m_ShaderLibrary.Load("Assets/Shader/ModelShader.glsl");
		m_ShaderLibrary.Load("Assets/Shader/Bong-Phong.glsl");
		

		m_Texture = Hazel::Texture2D::Creat("Assets/Texture/spot_texture.png");
		
	}
	
	void OnEvent(Hazel::Event& e) override
	{
		Hazel::EventDisPatcher dis(e);
		dis.Dispatch<Hazel::MouseScrolledEvent>(HZ_BIND_EVENT_FN(ExampleLayer::Move));
	}
	bool Move(Hazel::MouseScrolledEvent& e)
	{
		float x=e.GetYoffset();
		if (x == -1)
		{
			m_CamPosition.z += m_MoveSpeed;
		}
		else if (x == 1)
		{
			m_CamPosition.z -= m_MoveSpeed;
		}
		return false;
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("debug");
		ImGui::DragFloat3("model pos",&m_ModelPos[0]);
		ImGui::DragFloat("angle",&m_ModelAngle);
		ImGui::DragFloat3("camera pos", &m_CamPosition[0]);
		ImGui::DragFloat3("light pos", &m_LightPos[0]);
		ImGui::Separator();
		ImGui::DragFloat3("light ka", &m_light.GetKa()[0]);
		ImGui::DragFloat3("light kd", &m_light.GetKd()[0]);
		ImGui::DragFloat3("light ks", &m_light.GetKs()[0]);
		ImGui::DragFloat3("light AmbLightIntensity", &m_light.GetAmbLightIntensity()[0]);
		ImGui::DragFloat3("light LightIntensity", &m_light.GetLightIntensity()[0]);
		ImGui::End();
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{
		HZ_PROFILE_FUNCTION();

		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CamPosition.y -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CamPosition.y += m_MoveSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CamPosition.x -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CamPosition.x += m_MoveSpeed * ts;
		
		m_PerspectiveCamera.SetPosition(m_CamPosition);
		m_Model->SetPosition(m_ModelPos);
		m_Model->SetAngle(m_ModelAngle);
		m_light.SetPos(m_LightPos);


		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Ref<Hazel::Shader> shader = m_ShaderLibrary.Get("Bong-Phong");

		shader->SetInt1("u_Texture",0);

		Hazel::Render::BeginScene(m_PerspectiveCamera,m_light);
		m_Texture->Bind();
		shader->SetMat4("u_ModelMatrix", m_Model->GetModelMatrix());
		Hazel::Render::Submit(shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	float fov;
	glm::vec3 m_CamPosition;
	glm::vec3 m_LightPos;
	float m_MoveSpeed = 1.0f;

	glm::vec3 m_ModelPos;
	float m_ModelAngle;

	Hazel::Light m_light;

	Hazel::Ref < Hazel::Model> m_Model;

	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::PespectiveCamera m_PerspectiveCamera;

	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::Texture> m_Texture;

	
};

class  SandBox :public Hazel::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}
	~SandBox()
	{

	}

};

Hazel::Application* Hazel::CreatApplication()
{
	return new SandBox();
}
