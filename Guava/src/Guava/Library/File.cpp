#include "pch.h"
#include "File.h"

namespace Guava::File
{
	const Substring GetDirectory(const Substring path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('/');

		if (pos == std::string::npos)
			return "";

		return Substring(path.data(), pos + 1);
	}
	const Substring GetExtension(const Substring path)
	{
		if (path.empty())
			return "";

		size_t pos = path.find_last_of('.');

		if (pos == std::string::npos)
			return "";

		return Substring(path.data() + pos + 1);
	}
	
	TextFile::TextFile(Path path) :
		m_LinesExtracted(false)
	{
		std::ifstream file(path.data());

		if (file.is_open())
		{
			std::stringstream ss;
			ss << file.rdbuf();
			m_Content = ss.str();
		}

	}

	const Lines& TextFile::ExtractLines()
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

	const ContentView TextFile::GetContent() const
	{
		return m_Content;
	}

	const bool TextFile::IsEmpty() const
	{
		return m_Content.empty();
	}
}
