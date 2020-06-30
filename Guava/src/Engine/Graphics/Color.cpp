#include "pch.h"
#include "Color.h"

namespace Guava
{
	const Color Color::Red	=	Color(1.0f, 0.0f, 0.0f);
	const Color Color::Green =	Color(0.0f, 1.0f, 0.0f);
	const Color Color::Blue	=	Color(0.0f, 0.0f, 1.0f);
	const Color Color::White =	Color(1.0f, 1.0f, 1.0f);
	const Color Color::Black =	Color(0.0f, 0.0f, 0.0f);

	Color::Color(const float r, const float g, const float b, const float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Color::SetColor(const float r, const float g, const float b, const float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Color::SetColor(const Color& color)
	{
		*this = color;
	}

	const Color& Color::GetColor() const
	{
		return *this;
	}
}
