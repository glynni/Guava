#include "pch.h"
#include "string.h"

namespace Guava
{
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
