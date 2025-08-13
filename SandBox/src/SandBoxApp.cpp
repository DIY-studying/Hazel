#include <Hazel.h>
#include "Hazel/Core.h"
#include "Hazel/Render/gameobject/Model.h"

#include "imgui/imgui.h"

#include "string.h"

class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), fov(15),m_PerspectiveCamera(fov,1280/720),m_Position(0,0,3), m_ModelAngle(0),m_ModelPos(0)
	{
		m_VertexArray = Hazel::VertexArray::Creat();

		std::vector<Hazel::Ref<Hazel::Model>> models = Hazel::Model::Creat("Assets/Model/spot_quadrangulated.obj");

		m_Model = models[0];

		m_VertexArray->AddVertexBuffer(m_Model->GetVertexBuffer());
		m_VertexArray->SetIndexBuffer(m_Model->GetIndexBuffer());

		m_ShaderLibrary.Load("Assets/Shader/ModelShader.glsl");
		

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
			m_Position.z += m_MoveSpeed;
		}
		else if (x == 1)
		{
			m_Position.z -= m_MoveSpeed;
		}
		return false;
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("debug");
		ImGui::DragFloat3("model pos",&m_ModelPos[0]);
		ImGui::DragFloat("angle",&m_ModelAngle);
		ImGui::DragFloat3("camera pos", &m_Position[0]);
		ImGui::End();
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_Position.y -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_Position.y += m_MoveSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_Position.x -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_Position.x += m_MoveSpeed * ts;
		
		m_PerspectiveCamera.SetPosition(m_Position);
		m_Model->SetPosition(m_ModelPos);
		m_Model->SetAngle(m_ModelAngle);

		HZ_INFO("Pos: {0},{1},{2}",m_Model->GetPosition().x, m_Model->GetPosition().y,m_Model->GetPosition().z);

		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Ref<Hazel::Shader> shader = m_ShaderLibrary.Get("ModelShader");

		shader->SetInt1("u_Texture",0);

		Hazel::Render::BeginScene(m_PerspectiveCamera);
		m_Texture->Bind();
		shader->SetMat4("u_ModelMatrix", m_Model->GetModelMatrix());
		Hazel::Render::Submit(shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	float fov;
	glm::vec3 m_Position;
	float m_MoveSpeed = 1.0f;

	glm::vec3 m_ModelPos;
	float m_ModelAngle;

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
