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

}