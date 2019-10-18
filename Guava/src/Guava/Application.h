#pragma once
#include "Core.h"

namespace Guava
{
	class GUAVA_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}

