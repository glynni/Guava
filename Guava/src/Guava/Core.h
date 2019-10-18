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