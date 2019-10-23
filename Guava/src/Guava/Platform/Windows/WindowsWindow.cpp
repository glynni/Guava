#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Guava
{
	bool WindowsWindow::s_GlfwInitialized = false;

	Window* Window::Create(const std::string& title, unsigned int width, unsigned int height)
	{
		return new WindowsWindow(title, width, height);
	}

	WindowsWindow::WindowsWindow(const std::string& title, unsigned int width, unsigned int height)
		: Window(title, width, height)
	{
		if (!s_GlfwInitialized) {

			auto result = glfwInit();
			GUAVA_ASSERT(result == GLFW_TRUE, "GLFW could not be initialized!");
			s_GlfwInitialized = true;
		}

		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		GUAVA_ASSERT(m_Window != nullptr, "Window could not be opened!");
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
	}

	void WindowsWindow::PresentFrame()
	{
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::EnableVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}
}