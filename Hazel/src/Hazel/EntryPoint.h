#pragma once

#ifdef  HZ_PLATFORM_WINDOWS

#include "Log.h"
extern Hazel::Application*  Hazel::CreatApplication();

int main(int argc,char ** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("You can't do that.");
	HZ_ERROR("Something has problem.");


	auto app = Hazel::CreatApplication();
	app->Run();
	delete app;
}
#endif //  HZ_PLATFORM_WINDOWS
