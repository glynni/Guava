#pragma once
#include "Guava/Window.h"

namespace Guava
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const std::string& title, unsigned int width, unsigned int height);
		~WindowsWindow();

	private:

		static bool s_GlfwInitialized;
	};
}

