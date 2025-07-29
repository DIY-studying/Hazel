#pragma once

#include "Hazel/Render/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
	class OpenGLContext:public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);


		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_Window;
	};
}



