#pragma once
#include "Guava/Window.h"

struct GLFWwindow;

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

		bool AwaitsClosing() override;

	private:

		GLFWwindow* m_GlfwWindow;

		static bool			s_GlfwInitialized;
		static unsigned int s_WindowCount;
	};
}

