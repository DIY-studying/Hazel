#include <Hazel.h>
#include "Hazel/Core.h"
#include "Hazel/Render/gameobject/3D/Model.h"
#include "Hazel/Render/gameobject/3D/Cube.h"

#include "imgui/imgui.h"

#include "string.h"


class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), fov(15),m_CamPosition(0,0,10),
		m_ModelAngle(), m_ModelPos(), m_LightPos(), m_cubeposition()
	{
		m_PerspectiveCamera = Hazel::make_Ref<Hazel::PespectiveCamera>(fov, 1280.0f / 720.0f);
		m_light = Hazel::make_Ref<Hazel::Light>();

		std::vector<Hazel::Ref<Hazel::Model>> models = Hazel::Model::Creat("Assets/Model/spot_triangulated_good.obj");

		m_Model = models[0];

		m_ShaderLibrary.Load("Assets/Shader/ModelShader.glsl");
		m_ShaderLibrary.Load("Assets/Shader/Bong-Phong.glsl");

		m_cube= Hazel::make_Ref<Hazel::Cube>();
		

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
			m_CamPosition.z() += m_MoveSpeed;
		}
		else if (x == 1)
		{
			m_CamPosition.z() -= m_MoveSpeed;
		}
		return false;
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("debug");
		ImGui::DragFloat3("model pos",&m_ModelPos[0]);
		ImGui::DragFloat3("angle",&m_ModelAngle[0]);
		ImGui::DragFloat3("camera pos", &m_CamPosition[0]);
		ImGui::DragFloat3("cube pos", &m_cubeposition[0]);
		ImGui::DragFloat3("light pos", &m_LightPos[0]);
		ImGui::Separator();
		ImGui::DragFloat3("light ka", &m_light->GetKa()[0]);
		ImGui::DragFloat3("light kd", &m_light->GetKd()[0]);
		ImGui::DragFloat3("light ks", &m_light->GetKs()[0]);
		ImGui::DragFloat3("light AmbLightIntensity", &m_light->GetAmbLightIntensity()[0]);
		ImGui::DragFloat3("light LightIntensity", &m_light->GetLightIntensity()[0]);
		ImGui::End();
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{

		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CamPosition.y() -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CamPosition.y() += m_MoveSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CamPosition.x() -= m_MoveSpeed * ts;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CamPosition.x() += m_MoveSpeed * ts;
		
		m_PerspectiveCamera->SetPos(m_CamPosition);
		m_Model->SetPos(m_ModelPos);
		m_Model->SetAngle(m_ModelAngle);
		m_light->SetPos(m_LightPos);
		m_cube->SetPos(m_cubeposition);
		m_cube->SetAngle(m_ModelAngle);


		Hazel::RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Ref<Hazel::Shader> shader = m_ShaderLibrary.Get("Bong-Phong");

		shader->SetInt1("u_Texture",0);

		std::vector<Hazel::Ref<Hazel::GameObject>> gameobjs;
		gameobjs.push_back(m_light);
		gameobjs.push_back(m_Model);
		gameobjs.push_back(m_cube);

		Hazel::Render::BeginScene(m_PerspectiveCamera, shader);
		m_Texture->Bind();

		Hazel::Render::Submit(gameobjs);
		Hazel::Render::EndScene();
	}
private:
	float fov;
	Eigen::Vector3f m_CamPosition;
	Eigen::Vector3f m_LightPos;
	float m_MoveSpeed = 1.0f;

	Eigen::Vector3f m_ModelPos;
	Eigen::Vector3f m_ModelAngle;

	Eigen::Vector3f m_cubeposition;

	Hazel::Ref<Hazel::Light> m_light;

	Hazel::Ref < Hazel::Model> m_Model;

	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Ref<Hazel::PespectiveCamera> m_PerspectiveCamera;

	Hazel::Ref<Hazel::Texture> m_Texture;

	Hazel::Ref<Hazel::Cube> m_cube;

	
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
