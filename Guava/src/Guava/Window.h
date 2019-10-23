#pragma once
#include "Core.h"

#include <string>

namespace Guava
{
	class GUAVA_API Window
	{
	public:

		static Window* Create(const std::string& title, unsigned int width, unsigned int height);

		virtual ~Window() {};

	protected:

		Window(const std::string& title, unsigned int width, unsigned int height) {};

		std::string  m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};
}

