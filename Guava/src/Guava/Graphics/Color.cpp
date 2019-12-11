#include "pch.h"
#include "Color.h"

namespace Guava
{
	const Color Color::Red		= Color(1.0f, 0.0f, 0.0f);
	const Color Color::Green	= Color(0.0f, 1.0f, 0.0f);
	const Color Color::Blue		= Color(0.0f, 0.0f, 1.0f);
	const Color Color::White	= Color(1.0f, 1.0f, 1.0f);
	const Color Color::Black	= Color(0.0f, 0.0f, 0.0f);

	Color::Color(const float r, const float g, const float b, const float a)
	{
		x = r;
		y = g;
		z = b;
		w = a;
	}

	void Color::SetColor(const float r, const float g, const float b, const float a)
	{
		x = r;
		y = g;
		z = b;
		w = a;
	}

	void Color::SetColor(const Color& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;
		w = color.a;
	}

	const Color& Color::GetColor() const
	{
		return *this;
	}
}
