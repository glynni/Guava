#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Guava
{
	bool WindowsWindow::s_GlfwInitialized = false;
	unsigned int WindowsWindow::s_WindowCount = 0;

	Window* Window::Create(const std::string& title, unsigned int width, unsigned int height)
	{
		return new WindowsWindow(title, width, height);
	}

	WindowsWindow::WindowsWindow(const std::string& title, unsigned int width, unsigned int height) : Window(title, width, height)
	{
		if (!s_GlfwInitialized) 
		{
			auto result = glfwInit();
			GUAVA_ASSERT(result == GLFW_TRUE, "GLFW: Unable to initialize library.");
			GUAVA_CORE_INFO("GLFW: Initialized library.");
			s_GlfwInitialized = true;

			glfwSetErrorCallback([](int code, const char* msg) 
			{
				GUAVA_CORE_ERROR("GLFW: Error ({0}) {1}", code, msg);
			});
		}

		m_GlfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		s_WindowCount++;

		GUAVA_ASSERT(m_GlfwWindow != nullptr, "GLFW: Window could not be opened.");
		GUAVA_CORE_INFO("GLFW: Created Window #{0}.", s_WindowCount);

		glfwMakeContextCurrent(m_GlfwWindow);
	}

	WindowsWindow::~WindowsWindow()
	{
		GUAVA_CORE_INFO("GLFW: Closed Window #{0}", s_WindowCount);

		glfwDestroyWindow(m_GlfwWindow);
		s_WindowCount--;

		if (s_WindowCount == 0) 
		{
			glfwTerminate();
			GUAVA_CORE_INFO("GLFW: Terminated library.");
		}
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
	}

	void WindowsWindow::PresentFrame()
	{
		glfwSwapBuffers(m_GlfwWindow);
	}

	void WindowsWindow::EnableVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}
	
	bool WindowsWindow::AwaitsClosing()
	{
		return glfwWindowShouldClose(m_GlfwWindow);
	}
}