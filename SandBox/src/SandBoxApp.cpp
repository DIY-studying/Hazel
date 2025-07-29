#include <Hazel.h>

#include "imgui/imgui.h"

#include "memory.h"


class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example"),m_camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPosition(0)
	{
		float vertexs[6 * 3] = {
			-0.5f,-0.5f,0.0f,			0.8f,1.0f,1.0f,
			0.5f,-0.5f,0.0f,			1.0f,1.0f,0.1f,
			0.0f,0.5f,0.0f,			1.0f,0.2f,1.0f,
		};
		unsigned int indexs[3] = { 0,1,2 };

		m_VertexArray.reset(Hazel::VertexArray::Creat());
		m_VertexArray->Bind();


		std::shared_ptr <Hazel::VertexBuffer> vertexBuffer;
		std::shared_ptr <Hazel::IndexBuffer> indexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Creat(vertexs, sizeof(vertexs)));
		{
			Hazel::BufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);

			vertexBuffer->SetLayout(layout);
		}
		indexBuffer.reset(Hazel::IndexBuffer::Creat(indexs, sizeof(indexs) / sizeof(unsigned int)));


		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
				#version 330 core
				layout(location=0) in vec3 a_Position;
				layout(location=1) in vec3 a_Color;

				out vec3 v_Color;				
				uniform mat4 m_MVP;				

				void main()
				{
					v_Color=a_Color;
					gl_Position=m_MVP*vec4(a_Position,1.0f);
					//gl_Position=vec4(a_Position,1.0f);
				}
		)";
		std::string framentSrc = R"(
				#version 330 core
				out vec4 color;				
				
				in vec3 v_Color;
				void main()
				{
					color=vec4(0.8,0.3,0.2,1.0);
					color=vec4(v_Color,1.0f);
				}
		)";


		m_Shader.reset(new Hazel::Shader(vertexSrc, framentSrc));
	}
	
	void OnEvent(Hazel::Event& e) override
	{

	}

	void OnImGuiRender() override
	{
		
	}

	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CameraPosition.y -= m_MoveSpeed;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CameraPosition.y += m_MoveSpeed;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CameraPosition.x -= m_MoveSpeed;
		else if(Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CameraPosition.x += m_MoveSpeed;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_angle -= m_RotateSpeed;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_angle += m_RotateSpeed;


		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		m_camera.SetPosition(m_CameraPosition);
		m_camera.SetRotation(m_angle);

		Hazel::Render::BeginScene(m_camera);
		Hazel::Render::Submit(m_Shader, m_VertexArray);
		Hazel::Render::EndScene();
	}
private:
	std::shared_ptr <Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	Hazel::OrthoCamera m_camera;
	glm::vec3 m_CameraPosition;
	float m_angle = 0.0f;
	float m_MoveSpeed=0.01f;
	float m_RotateSpeed=2.0f;
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
