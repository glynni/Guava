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

		virtual void Update() = 0;
		virtual void PresentFrame() = 0;
		virtual void EnableVSync(bool enabled) = 0;

		virtual bool AwaitsClosing() = 0;

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		const std::string& GetTitle() const { return m_Title; }

	protected:

		Window(const std::string& title, unsigned int width, unsigned int height) : 
		m_Title(title), m_Width(width), m_Height(height){};

		std::string  m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};
}

