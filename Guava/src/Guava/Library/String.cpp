#include "pch.h"
#include "String.h"

namespace Guava
{
	void SplitString(const StringView str, const char splitBy, SubstringBuffer& output)
	{
		size_t start = 0, end = 0;
		output.clear();

		while (end != StringView::npos)
		{
			start = str.find_first_not_of(splitBy, end);
			end = str.find_first_of(splitBy, start);

			if (end != StringView::npos)
				output.emplace_back(str.data() + start, end - start);
			else
				output.emplace_back(str.data() + start, str.length() - start);
		}
	}
}
