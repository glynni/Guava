#pragma once
#include "Color.h"

namespace Guava
{
	struct Light
	{	
		float			Intensity = 1.0f;
		glm::vec4		Position;
		Guava::Color	Color;
	};
}

