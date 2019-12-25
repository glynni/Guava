#include "pch.h"
#include "File.h"

namespace Guava
{
	const string_view GetFileDirectory(const string_view path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('/');

		if (pos == string::npos)
			return "";

		return string_view(path.data(), pos + 1);
	}

	const string_view GetFileExtension(const string_view path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('.');

		if (pos == string::npos)
			return "";

		return string_view(path.data() + pos + 1);
	}
}
