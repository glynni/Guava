#pragma once
#include "Core.h"

namespace Guava
{
	class Window
	{
	public:
		
		struct Data
		{
			uvec2 Size;
		};

		// This is a static class matey
		Window() = delete;

		static bool Create(const string_view title, unsigned int width, unsigned int height);
		static void Destroy();

		static void PollEvents();
		static void WaitEvents();
		static void Present();
		static void EnableVSync(bool enabled);

		static bool ShouldClose();

		static const Data& GetData();
		static const uvec2 GetSize();
		static GLFWwindow* GetGLFW();
	};
}

