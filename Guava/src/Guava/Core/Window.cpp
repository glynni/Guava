#include "pch.h"
#include "Window.h"
#include "Guava/Graphics/Renderer.h"

namespace Guava
{
	static GLFWwindow* s_GlfwWindow = nullptr;
	static scope<Window::Data> s_Data;

	bool Window::Create(const string_view title, unsigned int width, unsigned int height)
	{
		auto result = glfwInit();
		GUAVA_ASSERT(result == GLFW_TRUE, "GLFW: Unable to initialize library.");

		glfwSetErrorCallback([](int code, const char* msg)
		{
			GUAVA_ERROR("GLFW error {0}: {1}", code, msg);
		});

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		s_GlfwWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

		GUAVA_ASSERT(s_GlfwWindow != nullptr, "GLFW: Window could not be opened.");
		GUAVA_INFO("GLFW: Opened Window");

		s_Data.reset(new Window::Data());
		s_Data->Size = { width, height };

		glfwMakeContextCurrent(s_GlfwWindow);

		glfwSetWindowSizeCallback(s_GlfwWindow, [](GLFWwindow* window, int w, int h) -> void
		{
			GUAVA_INFO("Window size changed. {0}x{1}", w, h);

			uvec2 size = {w, h};

			s_Data->Size = size;
			Renderer::SetWindowSize(size);
		});

		glfwSetFramebufferSizeCallback(s_GlfwWindow, [](GLFWwindow* window, int w, int h) -> void
		{
			
		});

		return true;
	}

	void Window::Destroy()
	{
		GUAVA_INFO("GLFW: Closed Window");

		glfwDestroyWindow(s_GlfwWindow);

		glfwTerminate();

		s_Data.reset(nullptr);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::WaitEvents()
	{
		glfwWaitEvents();
	}

	void Window::Present()
	{
		glfwSwapBuffers(s_GlfwWindow);
	}

	void Window::EnableVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}
	
	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(s_GlfwWindow);
	}

	const Window::Data& Window::GetData()
	{
		return *s_Data.get();
	}

	const uvec2 Window::GetSize()
	{
		return s_Data->Size;
	}

	void* Window::GetGLFWPointer()
	{
		return s_GlfwWindow;
	}
}