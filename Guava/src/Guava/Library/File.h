#pragma once
namespace Guava::File
{
	using Line = StringView;
	using Lines = std::vector<Line>;
	using Path = const StringView;
	using Content = std::string;
	using ContentView = const StringView;

	const Substring GetDirectory(Path path);
	const Substring GetExtension(Path path);

	class TextFile
	{
	public:

		TextFile(Path path);

		const Lines& ExtractLines();
		const ContentView GetContent() const;
		const bool IsEmpty() const;

	private:

		Content m_Content;
		Lines	m_Lines;

		bool m_LinesExtracted;
	};
}

