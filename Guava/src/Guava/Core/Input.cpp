#include "pch.h"
#include "Input.h"
#include "Window.h"

namespace Guava
{
	// Keyboard
	static std::vector<bool> s_KeyDown;

	// Mouse
	static std::vector<bool>	s_MouseButtonDown;
	static glm::vec2			s_MousePos;
	static glm::vec2			s_MousePosPrevious;
	static glm::vec2			s_MousePosChange;

	void Input::Create()
	{
		GLFWwindow* window = (GLFWwindow*)Window::GetGLFWPointer();
		glm::dvec2 mousePos;

		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		s_MousePos = s_MousePosPrevious = mousePos;

		s_KeyDown.resize(GLFW_KEY_LAST + 1, false);
		s_MouseButtonDown.resize(GLFW_MOUSE_BUTTON_LAST + 1, false);

		glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			s_KeyDown[key] = action != GLFW_RELEASE;
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
		{
			s_MouseButtonDown[button] = action != GLFW_RELEASE;
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y)
		{
			s_MousePos = { x, y };
			s_MousePosChange = s_MousePos - s_MousePosPrevious;
			s_MousePosPrevious = s_MousePos;
		});
	}

	void Input::Destroy()
	{
		s_KeyDown = std::vector<bool>();
	}

	void Input::Update(const bool waitForInput)
	{
		s_MousePosChange = { 0.f, 0.f };

		if (waitForInput)
			Window::WaitEvents();
		else
			Window::PollEvents();
	}

	const bool Input::KeyDown(const Key key)
	{
		return s_KeyDown.at((unsigned int)key);
	}

	const bool Input::MouseDown(const MouseButton btn)
	{
		return s_MouseButtonDown.at((unsigned int)btn);
	}

	const glm::vec2& Input::GetMousePosition()
	{
		return s_MousePos;
	}
	const glm::vec2& Input::GetMouseMovement()
	{
		return s_MousePosChange;
	}
}
