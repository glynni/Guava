#include "pch.h"
#include "TextFile.h"
#include "ResourceManager.h"

namespace Guava
{
	TextFile::TextFile(const string_view path) :
		m_LinesExtracted(false)
	{
		LoadFromFile(path);
	}

	const vector<string_view>& TextFile::ExtractLines()
	{
		if (!m_LinesExtracted)
		{
			size_t start = 0;

			for (size_t i = 0; i < m_Content.length(); ++i)
			{
				if (m_Content[i] == '\n')
				{
					m_Lines.emplace_back(m_Content.data() + start, i - start);
					start = i + 1;
				}
			}

			m_LinesExtracted = true;
		}

		return m_Lines;
	}

	const string_view TextFile::GetContent() const
	{
		return m_Content;
	}

	const bool TextFile::IsEmpty() const
	{
		return m_Content.empty();
	}

	void TextFile::LoadFromFile(const string_view path)
	{
		ifstream file(path.data());

		if (file.is_open())
		{
			stringstream ss;
			ss << file.rdbuf();
			m_Content = ss.str();
		}
		else
			GUAVA_ERROR("Failed to open text file: {0}", path.data());
	}
}
