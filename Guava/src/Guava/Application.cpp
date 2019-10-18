#include "Application.h"
#include "Log.h"

namespace Guava
{
	Application::Application()
	{
		GUAVA_CORE_INFO("Success message from the engine! Success code: {0}", 110);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{

		}
	}
}
