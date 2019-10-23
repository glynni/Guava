#pragma once
#include "Guava/Window.h"

class GLFWwindow;

namespace Guava
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const std::string& title, unsigned int width, unsigned int height);
		~WindowsWindow();

		void Update() override;
		void PresentFrame() override;
		void EnableVSync(bool enabled) override;

	private:

		static bool s_GlfwInitialized;
		GLFWwindow* m_Window;
	};
}

