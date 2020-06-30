#include "pch.h"
#include "Core.h"

namespace Guava
{
	const string_view GetFileDirectory(const string_view path)
	{
		if (path.empty())
			return string_view();

		size_t pos = path.find_last_of('/');

		if (pos == string::npos)
			return string_view();

		return string_view(path.data(), pos + 1);
	}
	const string_view GetFileExtension(const string_view path)
	{
		if (path.empty())
			return string_view();

		size_t pos = path.find_last_of('.');

		if (pos == string::npos)
			return string_view();

		return string_view(path.data() + pos + 1);
	}
	const string_view GetFileName(const string_view path)
	{
		if (path.empty())
			return string_view();

		size_t pos = path.find_last_of('/');

		if (pos == string::npos)
			return path.data();

		return string_view(path.data() + pos + 1);
	}

	void SplitString(const string_view str, const char splitBy, vector<string_view>& output)
	{
		size_t start = 0, end = 0;
		output.clear();

		while (end != string_view::npos)
		{
			start = str.find_first_not_of(splitBy, end);
			end = str.find_first_of(splitBy, start);

			if (end != string_view::npos)
				output.emplace_back(str.data() + start, end - start);
			else
				output.emplace_back(str.data() + start, str.length() - start);
		}
	}
}