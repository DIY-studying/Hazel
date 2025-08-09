#pragma once

#ifdef  HZ_PLATFORM_WINDOWS

#include "Log.h"
extern Hazel::Application*  Hazel::CreatApplication();

int main(int argc,char ** argv)
{
	Hazel::Log::Init();

	auto app = Hazel::CreatApplication();
	app->Run();
	delete app;

	return 0;
}

#endif //  HZ_PLATFORM_WINDOWS
