#pragma once

#ifdef GUAVA_PLATFORM_WINDOWS

extern Guava::Application* Guava::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Guava::CreateApplication();

	app->Run();

	delete app;

	return 0;
}

#endif
