#pragma once
#include "Guava/Core/Core.h"

namespace Guava
{
	struct  Color : public glm::vec4
	{
		Color(const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);

		void SetColor(const float r, const float g, const float b, const float a);
		void SetColor(const Color& color);

		const Color& GetColor() const;

		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
	};
}

