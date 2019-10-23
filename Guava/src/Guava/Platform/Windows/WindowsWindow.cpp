#include "WindowsWindow.h"

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
			GUAVA_ASSERT(result == GLFW_OK, "GLFW could not be initialized!");
			s_GlfwInitialized = true;
		}
	}

	WindowsWindow::~WindowsWindow()
	{
	}
}