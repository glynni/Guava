#pragma once
#include "Guava/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Guava
{
	class Logger
	{
	public:

		typedef std::shared_ptr<spdlog::logger> LogPtr;

		inline static void Create()
		{
			spdlog::set_pattern("%n %v%$");

			s_CoreLogger = spdlog::stderr_color_mt("[GUAVA]");
			s_CoreLogger->set_level(spdlog::level::trace);
		}

		inline static LogPtr& GetCoreLogger() { return s_CoreLogger; }

	private:

		static LogPtr s_CoreLogger;
	};
}

// Core logger
#if defined TRUE
	#define GUAVA_CORE_ERROR(...) ::Guava::Logger::GetCoreLogger()->error(__VA_ARGS__)
	#define GUAVA_CORE_WARN(...)  ::Guava::Logger::GetCoreLogger()->warn(__VA_ARGS__)
	#define GUAVA_CORE_INFO(...)  ::Guava::Logger::GetCoreLogger()->info(__VA_ARGS__)
	#define GUAVA_CORE_TRACE(...) ::Guava::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#endif