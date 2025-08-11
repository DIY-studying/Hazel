#include <Hazel.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Render/gameobject/Model.h"
#include "string.h"

class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), fov(15),m_PerspectiveCamera(fov,1280/720),m_Position(0)
	{
		m_VertexArray = Hazel::VertexArray::Creat();

		Hazel::Model bunny = Hazel::Model("Assets/Model/spot_quadrangulated.obj");

		m_VertexArray->AddVertexBuffer(bunny.GetVertexBuffer());
		m_VertexArray->SetIndexBuffer(bunny.GetIndexBuffer());

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

		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Ref<Hazel::Shader> shader = m_ShaderLibrary.Get("ModelShader");

		dynamic_cast<Hazel::OpenGLShader*>(shader.get())->SetUniformInt1(0,"u_Texture");

		Hazel::Render::BeginScene(m_PerspectiveCamera);
		m_Texture->Bind();
		Hazel::Render::Submit(shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	float fov;
	glm::vec3 m_Position;
	float m_MoveSpeed = 1.0f;

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
