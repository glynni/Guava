#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Guava
{
	class GUAVA_API Log
	{
	public:

		typedef std::shared_ptr<spdlog::logger> LogPtr;

		static void Init();

		inline static LogPtr& GetCoreLogger() { return s_CoreLogger; }
		inline static LogPtr& GetClientLogger() { return s_ClientLogger; }

	private:

		static LogPtr s_CoreLogger;
		static LogPtr s_ClientLogger;
	};
}

// Core logger
#if defined GUAVA_DEBUG && defined GUAVA_BUILD_DLL
#define GUAVA_CORE_ERROR(...) ::Guava::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GUAVA_CORE_WARN(...)  ::Guava::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GUAVA_CORE_INFO(...)  ::Guava::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GUAVA_CORE_TRACE(...) ::Guava::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GUAVA_CORE_FATAL(...) ::Guava::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#elif defined GUAVA_BUILD_DLL
#define GUAVA_CORE_ERROR(...)
#define GUAVA_CORE_WARN(...) 
#define GUAVA_CORE_INFO(...) 
#define GUAVA_CORE_TRACE(...)
#define GUAVA_CORE_FATAL(...)
#endif

#define GUAVA_INVALID_RENDER_API(obj) GUAVA_ASSERT(false, "{0} could not be created: Invalied API specified ({1})", obj, Renderer::GetAPI());

// Client logger
#if defined GUAVA_DEBUG && !defined GUAVA_BUILD_DLL
#define GUAVA_ERROR(...) ::Guava::Log::GetClientLogger()->error(__VA_ARGS__)
#define GUAVA_WARN(...)  ::Guava::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GUAVA_INFO(...)  ::Guava::Log::GetClientLogger()->info(__VA_ARGS__)
#define GUAVA_TRACE(...) ::Guava::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GUAVA_FATAL(...) ::Guava::Log::GetClientLogger()->fatal(__VA_ARGS__)
#elif !defined GUAVA_BUILD_DLL
#define GUAVA_ERROR(...)
#define GUAVA_WARN(...) 
#define GUAVA_INFO(...) 
#define GUAVA_TRACE(...)
#define GUAVA_FATAL(...)
#endif
