#include "pch.h"
#include "BufferLayout.h"

namespace Guava
{
	namespace Buffer
	{
		Layout::Layout(std::initializer_list<Attribute::Type> TypesInOrder) :
			Stride(0)
		{
			size_t offset = 0, size = 0;
			unsigned int numElements = 0;

			for (auto type : TypesInOrder)
			{
				switch (type)
				{
				case Attribute::Type::Vec2f:
					numElements = 2;
					size = sizeof(float) * numElements;
					break;

				case Attribute::Type::Vec3f:
					numElements = 3;
					size = sizeof(float) * numElements;
					break;

				case Attribute::Type::Vec4f:
					numElements = 4;
					size = sizeof(float) * numElements;
					break;

				case Attribute::Type::Mat4f:
					numElements = 4 * 4;
					size = sizeof(float) * numElements;
					break;

				default:
					GUAVA_ASSERT(false, "Wrong attribute-type specified!");
				}

				Attributes.emplace_back(type, numElements, size, offset);
				offset += size;
			}

			Stride = offset;
		}

		Attribute::Attribute(Attribute::Type t, unsigned int numEl, size_t s, size_t o) :
			AttributeType(t),
			NumElements(numEl),
			Size(s),
			Offset(o)
		{

		}
	}
}
