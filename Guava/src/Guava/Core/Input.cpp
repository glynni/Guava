#include "pch.h"
#include "Input.h"
#include "Window.h"

namespace Guava
{
	// Keyboard
	static vector<bool> s_KeyDown;
	static vector<int> s_KeyChange;

	// Mouse
	static vector<bool>	s_MouseButtonDown;
	static vector<int>	s_MouseButtonChange;
	static vec2			s_MousePos;
	static vec2			s_MousePosPrevious;
	static vec2			s_MousePosChange;

	void Input::Create()
	{
		GLFWwindow* window = (GLFWwindow*)Window::GetGLFWPointer();
		dvec2 mousePos;

		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		s_MousePos = s_MousePosPrevious = mousePos;

		s_KeyDown.resize(GLFW_KEY_LAST + 1, false);
		s_KeyChange.resize(GLFW_KEY_LAST + 1, 0);

		s_MouseButtonDown.resize(GLFW_MOUSE_BUTTON_LAST + 1, false);
		s_MouseButtonChange.resize(GLFW_MOUSE_BUTTON_LAST + 1, 0);

		glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			bool oldState = s_KeyDown[key];
			bool newState = action != GLFW_RELEASE;

			if (oldState && !newState)
				s_KeyChange[key] = -1;
			else if(!oldState && newState)
				s_KeyChange[key] = 1;

			s_KeyDown[key] = newState;
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
		{
			bool oldState = s_MouseButtonDown[button];
			bool newState = action != GLFW_RELEASE;

			if (oldState && !newState)
				s_MouseButtonChange[button] = -1;
			else if (!oldState && newState)
				s_MouseButtonChange[button] = 1;

			s_MouseButtonDown[button] = newState;
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
		s_KeyDown = vector<bool>();
	}

	void Input::Update(const bool waitForInput)
	{
		s_MousePosChange = { 0.f, 0.f };
		s_KeyChange.assign(s_KeyChange.size(), 0);
		s_MouseButtonChange.assign(s_MouseButtonChange.size(), 0);

		if (waitForInput)
			Window::WaitEvents();
		else
			Window::PollEvents();
	}

	const bool Input::KeyDown(const Key key)
	{
		return s_KeyDown.at((unsigned int)key);
	}

	const bool Input::KeyPress(const Key key)
	{
		return s_KeyChange.at((unsigned int)key) == 1;
	}

	const bool Input::KeyRelease(const Key key)
	{
		return s_KeyChange.at((unsigned int)key) == -1;
	}

	const bool Input::MouseDown(const MouseButton btn)
	{
		return s_MouseButtonDown.at((unsigned int)btn);
	}

	const bool Input::MousePress(const MouseButton btn)
	{
		return s_MouseButtonChange.at((unsigned int)btn) == 1;
	}

	const bool Input::MouseRelease(const MouseButton btn)
	{
		return s_MouseButtonChange.at((unsigned int)btn) == -1;
	}

	const vec2& Input::GetMousePosition()
	{
		return s_MousePos;
	}
	const vec2& Input::GetMouseMovement()
	{
		return s_MousePosChange;
	}
}
