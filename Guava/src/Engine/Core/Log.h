#pragma once

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

		inline static void Destroy()
		{
			s_CoreLogger.reset();
		}

		inline static LogPtr& GetCoreLogger() { return s_CoreLogger; }

	private:

		static LogPtr s_CoreLogger;
	};
}

// Core logger
#if 1 or GUAVA_DEBUG
	#define GUAVA_ERROR(...) ::Guava::Logger::GetCoreLogger()->error(__VA_ARGS__)
	#define GUAVA_WARN(...)  ::Guava::Logger::GetCoreLogger()->warn(__VA_ARGS__)
	#define GUAVA_INFO(...)  ::Guava::Logger::GetCoreLogger()->info(__VA_ARGS__)
	#define GUAVA_TRACE(...) ::Guava::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#else
	#define GUAVA_ERROR(...)
	#define GUAVA_WARN(...) 
	#define GUAVA_INFO(...) 
	#define GUAVA_TRACE(...)
#endif