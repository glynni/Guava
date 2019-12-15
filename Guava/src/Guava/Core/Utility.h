#pragma once

namespace Guava
{
	std::string ReadTextFile(const std::string_view path);
	std::string GetFileDirectory(const std::string_view path);
	std::string GetFileExtension(const std::string_view path);
}
