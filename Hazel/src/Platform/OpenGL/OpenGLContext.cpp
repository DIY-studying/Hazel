#include "hzpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "OpenGLError.h"

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize glad.");
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void OpenGLContext::PrintVersionInfo()
	{
		const char* version = (const char*)glGetString(GL_VERSION);
		const char* vendor = (const char*)glGetString(GL_VENDOR);
		const char* renderer = (const char*)glGetString(GL_RENDERER);

		HZ_CORE_INFO("OpenGL Version: {0}, Vendor: {1}, Renderer: {2}", version, vendor, renderer);
	}
}