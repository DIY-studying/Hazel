#include <Hazel.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0), m_Color()
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
		vertexBuffer.reset(Hazel::VertexBuffer::Creat(vertexs, sizeof(vertexs)));
		{
			Hazel::BufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(2);

			vertexBuffer->SetLayout(layout);
		}
		indexBuffer.reset(Hazel::IndexBuffer::Creat(indexs, sizeof(indexs) / sizeof(unsigned int)));


		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
				#version 330 core
				layout(location=0) in vec3 a_Position;
				layout(location=1) in vec2 a_TexCor;
				
				uniform mat4 u_ViewProject;				
				out vec2 v_TexCor;	

				void main()
				{
					v_TexCor=a_TexCor;
					gl_Position=u_ViewProject*vec4(a_Position,1.0f);
				}
		)";
		std::string framentSrc = R"(
				#version 330 core
				out vec4 color;				
				
				uniform sampler2D  u_Texture;
				in vec2 v_TexCor;	
				void main()
				{
					color=texture(u_Texture,v_TexCor);
				}
		)";


		m_Shader.reset(Hazel::Shader::Creat(vertexSrc, framentSrc));
		m_Texture1 = Hazel::Texture2D::Creat("Assets/image/awesomeface.png");
		m_Texture2 = Hazel::Texture2D::Creat("Assets/image/container.jpg");
		dynamic_cast<Hazel::OpenGLShader*>(m_Shader.get())->SetUniformFloat3(m_Color, "u_Color");
		dynamic_cast<Hazel::OpenGLShader*>(m_Shader.get())->SetUniformFloat3(m_Color, "u_Texture");
	}
	
	void OnEvent(Hazel::Event& e) override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("debug");
		ImGui::End();
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CameraPosition.y -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CameraPosition.y += m_MoveSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CameraPosition.x -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CameraPosition.x += m_MoveSpeed * ts;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_angle -= m_RotateSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_angle += m_RotateSpeed * ts;


		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		m_camera.SetPosition(m_CameraPosition);
		m_camera.SetRotation(m_angle);

		Hazel::Render::BeginScene(m_camera);
		m_Texture1->Bind();
		Hazel::Render::Submit(m_Shader, m_VertexArray);
		m_Texture2->Bind();
		Hazel::Render::Submit(m_Shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	Hazel::Ref <Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Texture> m_Texture1,m_Texture2;

	Hazel::OrthoCamera m_camera;
	glm::vec3 m_CameraPosition;
	float m_angle = 0.0f;
	float m_MoveSpeed = 5.f;;
	float m_RotateSpeed=30.0f;
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
