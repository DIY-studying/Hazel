#include <Hazel.h>


class  ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}
	
	void OnEvent(Hazel::Event& e) override
	{
		HZ_TRACE("{0} ", e.ToString());
	}

	void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();
	}

	void OnUpdate() override
	{
		HZ_INFO("ExamplLayer: update");
	}

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
