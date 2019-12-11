#pragma once
#include "Mesh.h"

namespace Guava
{
	class Model
	{
	public:

		Model(const std::string_view filePath);

		static Model* Create(const std::string_view filePath);
	};
}

