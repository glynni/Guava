#include "File.h"
#include "Log.h"

#include <fstream>
#include <sstream>

namespace Guava
{
	std::string File::ReadTextFile(const std::string& path)
	{
		std::ifstream file(path);

		if (file.is_open())
		{
			std::stringstream ss;
			ss << file.rdbuf();

			return ss.str();
		}
		else
			GUAVA_CORE_ERROR("File could not be opened: {0}", path);

		return "";
	}
}
