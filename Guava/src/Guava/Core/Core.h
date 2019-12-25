#pragma once

#define GUAVA_EXECUTION_POLICY std::execution::par_unseq

#ifdef GUAVA_DEBUG
#define GUAVA_ASSERT(x, ...) { if(!(x)) { GUAVA_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GUAVA_ASSERT(x, ...)
#endif