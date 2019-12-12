#pragma once
#include "Guava/Core/Core.h"

namespace Guava
{
	struct  ColorRGBA : public glm::vec4
	{
		ColorRGBA(const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);

		void SetColor(const float r, const float g, const float b, const float a);
		void SetColor(const ColorRGBA& color);

		const ColorRGBA& GetColor() const;

		static const ColorRGBA Red;
		static const ColorRGBA Green;
		static const ColorRGBA Blue;
		static const ColorRGBA White;
		static const ColorRGBA Black;
	};
}

