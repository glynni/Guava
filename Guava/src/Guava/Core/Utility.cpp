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

	std::string GetFileDirectory(const std::string_view path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('/');

		if (pos == std::string::npos)
			return "";
			
		return std::string(path.substr(0, pos + 1));
	}

	std::string GetFileExtension(const std::string_view path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('.');

		if (pos == std::string::npos)
			return "";

		return std::string(path.substr(pos + 1));
	}
}
