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
		bool m_Running;
	};

	// To be defined in client
	Application* CreateApplication();
}

