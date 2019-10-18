#include "Log.h"

namespace Guava
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n %v%$");

		s_CoreLogger = spdlog::stderr_color_mt("[GUAVA]");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("[CLIENT]");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
