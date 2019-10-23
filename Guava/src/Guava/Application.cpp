#include "Application.h"
#include "Log.h"

namespace Guava
{
	Application::Application() :
		m_Window(Window::Create("Guava", 1280, 720)),
		m_Running(true)
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_Window->EnableVSync(true);

		while (m_Running)
		{
			m_Window->Update();
			m_Window->PresentFrame();
		}
	}
}
