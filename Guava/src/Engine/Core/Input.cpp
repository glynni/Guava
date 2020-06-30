#include "pch.h"
#include "Input.h"
#include "Window.h"

namespace Guava
{
	static scope<Input> Instance;

	void Input::Create()
	{
		Instance.reset(new Input());
	}

	void Input::Destroy()
	{
		Instance.reset();
	}

	void Input::Update(const bool waitForInput)
	{
		Instance->m_MousePosChange = { 0.f, 0.f };

		if (waitForInput)
			Window::WaitEvents();
		else
			Window::PollEvents();
	}

	const bool Input::KeyDown(const Key key)
	{
		return glfwGetKey(Window::GetGLFW(), (int)key) == GLFW_PRESS;
	}

	const bool Input::MouseDown(const MouseButton btn)
	{
		return glfwGetMouseButton(Window::GetGLFW(), (int)btn) == GLFW_PRESS;
	}

	const vec2& Input::GetMousePosition()
	{
		return Instance->m_MousePos;
	}

	const vec2& Input::GetMouseMovement()
	{
		return Instance->m_MousePosChange;
	}

	Input::Input()
	{
		GLFWwindow* window = (GLFWwindow*)Window::GetGLFW();
		dvec2 mousePos;

		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		m_MousePos = m_MousePosPrevious = mousePos;

		glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			// Fire some event
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
		{
			// Fire some event
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y)
		{
			Input& i = *Instance.get();

			i.m_MousePos = { x, y };
			i.m_MousePosChange = i.m_MousePos - i.m_MousePosPrevious;
			i.m_MousePosPrevious = i.m_MousePos;
		});
	}
}
