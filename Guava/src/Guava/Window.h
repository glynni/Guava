#pragma once
#include "Log.h"

#include <string>

namespace Guava
{
	class GUAVA_API Window
	{
	public:

		static Window* Create(const std::string& title, unsigned int width, unsigned int height);

		virtual ~Window() {};

		virtual void Update() = 0;
		virtual void PresentFrame() = 0;
		virtual void EnableVSync(bool enabled) = 0;

	protected:

		Window(const std::string& title, unsigned int width, unsigned int height) {};

		std::string  m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};
}

