#include <Hazel.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/OrthoCameraController.h"
#include "string.h"

class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController((float)1280.0f/720.0f), m_Color()
	{
		float vertexs[5 * 4] = {
			-0.5f,-0.5f,0.0f,			0.0f,0.0f,
			0.5f,-0.5f,0.0f,			1.0f,0.0f,
			0.5f,0.5f,0.0f,			1.0f,1.0f,
			-0.5f,0.5f,0.0f,			0.0f,1.0f
		};
		unsigned int indexs[3*2] = { 0,1,2,2,3,0 };

		m_VertexArray.reset(Hazel::VertexArray::Creat());
		m_VertexArray->Bind();


		Hazel::Ref <Hazel::VertexBuffer> vertexBuffer;
		Hazel::Ref <Hazel::IndexBuffer> indexBuffer;
		vertexBuffer = (Hazel::VertexBuffer::Creat(vertexs, sizeof(vertexs)));
		{
			Hazel::BufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(2);
			vertexBuffer->SetLayout(layout);
		}
		indexBuffer=Hazel::IndexBuffer::Creat(indexs, sizeof(indexs) / sizeof(unsigned int));


		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_ShaderLibrary.Load("Assets/Shader/Texture.glsl");
		

		m_Texture1 = Hazel::Texture2D::Creat("Assets/Texture/awesomeface.png");
		m_Texture2 = Hazel::Texture2D::Creat("Assets/Texture/container.jpg");
		
	}
	
	void OnEvent(Hazel::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("debug");
		ImGui::End();
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{
		
		m_CameraController.OnUpdate(ts);
		//HZ_CORE_INFO("{0}",std::to_string( m_CameraController.GetZoom()));

		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Ref<Hazel::Shader> shader = m_ShaderLibrary.Get("Texture");
		dynamic_cast<Hazel::OpenGLShader*>(shader.get())->SetUniformFloat3(m_Color, "u_Color");
		dynamic_cast<Hazel::OpenGLShader*>(shader.get())->SetUniformFloat3(m_Color, "u_Texture");

		Hazel::Render::BeginScene(m_CameraController.GetCamera());
		m_Texture2->Bind();
		Hazel::Render::Submit(shader, m_VertexArray);
		m_Texture1->Bind();
		Hazel::Render::Submit(shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::OrthoCameraController m_CameraController;

	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::Texture> m_Texture1,m_Texture2;

	glm::vec3 m_Color;
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
