#pragma once

namespace Guava
{
	class TextFile
	{
	public:

		const vector<string_view>& ExtractLines();
		const string_view GetContent() const;
		const bool IsEmpty() const;

		TextFile(const string_view path);

	private:

		void LoadFromFile(const string_view path);

		string				m_Content;
		vector<string_view>	m_Lines;
		bool				m_LinesExtracted;
	};
}