#pragma once

#define GUAVA_EXECUTION_POLICY std::execution::par_unseq

#ifdef GUAVA_DEBUG
#define GUAVA_ASSERT(x, ...) { if(!(x)) { GUAVA_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GUAVA_ASSERT(x, ...)
#endif

namespace Guava
{
	// Some utility functions
	const string_view GetFileDirectory(const string_view path);
	const string_view GetFileExtension(const string_view path);
	const string_view GetFileName(const string_view path);

	void SplitString(const string_view str, const char splitBy, vector<string_view>& output);
}