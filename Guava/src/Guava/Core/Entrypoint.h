#pragma once

#ifdef GUAVA_PLATFORM_WINDOWS

extern Guava::Application* Guava::CreateApplication();

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Guava::Log::Init();

	auto app = Guava::CreateApplication();
	app->Run();
	delete app;

	getchar();

	return 0;
}

#endif
