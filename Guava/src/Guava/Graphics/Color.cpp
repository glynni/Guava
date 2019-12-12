#include "pch.h"
#include "Color.h"

namespace Guava
{
	const ColorRGBA ColorRGBA::Red		= ColorRGBA(1.0f, 0.0f, 0.0f);
	const ColorRGBA ColorRGBA::Green	= ColorRGBA(0.0f, 1.0f, 0.0f);
	const ColorRGBA ColorRGBA::Blue		= ColorRGBA(0.0f, 0.0f, 1.0f);
	const ColorRGBA ColorRGBA::White	= ColorRGBA(1.0f, 1.0f, 1.0f);
	const ColorRGBA ColorRGBA::Black	= ColorRGBA(0.0f, 0.0f, 0.0f);

	ColorRGBA::ColorRGBA(const float r, const float g, const float b, const float a)
	{
		x = r;
		y = g;
		z = b;
		w = a;
	}

	void ColorRGBA::SetColor(const float r, const float g, const float b, const float a)
	{
		x = r;
		y = g;
		z = b;
		w = a;
	}

	void ColorRGBA::SetColor(const ColorRGBA& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;
		w = color.a;
	}

	const ColorRGBA& ColorRGBA::GetColor() const
	{
		return *this;
	}
}
