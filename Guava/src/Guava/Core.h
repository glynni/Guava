#pragma once

#ifdef GUAVA_PLATFORM_WINDOWS
	#ifdef GUAVA_BUILD_DLL
		#define GUAVA_API _declspec(dllexport)
	#else 
		#define GUAVA_API _declspec(dllimport)
	#endif
#else
	#error Guava only supports Windows!
#endif

#ifdef GUAVA_DEBUG
#define GUAVA_ASSERT(x, ...) { if(!(x)) { GUAVA_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GUAVA_ASSERT(x, ...)
#endif