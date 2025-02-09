#include <Hazel.h>

class  SandBox :public Hazel::Application
{
public:
	SandBox()
	{

	}
	~SandBox()
	{

	}

};
Hazel::Application* Hazel::CreatApplication()
{
	return new SandBox();
}
