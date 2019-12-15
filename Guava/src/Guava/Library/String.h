#pragma once
namespace Guava
{
	using String = std::string;
	using StringView = std::string_view;
	using Substring = StringView;
	using SubstringBuffer = std::vector<Substring>;

	void SplitString(const StringView str, const char splitBy, SubstringBuffer& output);
}

