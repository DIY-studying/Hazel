#include "hzpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Hazel/Application.h"

namespace Hazel
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		if(state== GLFW_KEY_UNKNOWN)
		{
			HZ_CORE_ERROR("Unknown keycode: {0}", keycode);
			return false;
		}
		return state==GLFW_PRESS || state==GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		
		return { (float)xPos, (float)yPos };
	}
}


