#pragma once
#include "Color.h"

namespace Guava
{
	struct Light
	{	
		float		Intensity = 1.0f;
		glm::vec3	Position;
		ColorRGBA	Color;
	};
}

