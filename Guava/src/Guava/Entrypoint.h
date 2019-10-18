#pragma once

#ifdef GUAVA_PLATFORM_WINDOWS

extern Guava::Application* Guava::CreateApplication();

int main(int argc, char** argv)
{
	Guava::Log::Init();

	auto app = Guava::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
