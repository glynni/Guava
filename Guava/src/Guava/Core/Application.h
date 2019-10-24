#pragma once
#include "Core.h"
#include "Window.h"

#include <memory>

namespace Guava
{
	class GUAVA_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();

	private:

		std::unique_ptr<Window> m_Window;
	};

	// To be defined in client
	Application* CreateApplication();
}

