#include "pch.h"
#include "Utility.h"

namespace Guava
{
	std::string ReadTextFile(const std::string_view path)
	{
		std::ifstream file(path.data());

		if (file.is_open())
		{
			std::stringstream ss;
			ss << file.rdbuf();

			return ss.str();
		}
		else
		{
			return "";
			GUAVA_CORE_ERROR("Textfile could not be opened: {0}", path);
		}
	}
}
