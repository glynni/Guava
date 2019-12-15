#pragma once
#include "Texture.h"
#include "Color.h"

namespace Guava
{
	namespace Buffer
	{
		struct Attribute
		{
			enum class Type
			{
				Vec2f,
				Vec3f,
				Vec4f,
				Mat4f
			};

			Attribute(Attribute::Type type, unsigned int numElements, size_t size, size_t offset);

			Type AttributeType;
			unsigned int NumElements;
			size_t Size;
			size_t Offset;
		};

		struct Layout
		{
			Layout(std::initializer_list<Attribute::Type> typesInOrder);

			size_t Stride;

			std::vector<Attribute> Attributes;
		};
	};
}


