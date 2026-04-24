#include "hzpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initailize glad.");
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void OpenGLContext::PrintVersionInfo()
	{
		const char* version = (const char*)glGetString(GL_VERSION);			// 版本
		const char* vendor = (const char*)glGetString(GL_VENDOR);				// 显卡厂商
		const char* renderer = (const char*)glGetString(GL_RENDERER);		// 显卡型号


		HZ_CORE_INFO("OpenGL 版本: {0},厂商: {1}, 显卡: {2} ", version, vendor, renderer);
	}

}