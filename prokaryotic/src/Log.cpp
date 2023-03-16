#include "Log.h"


namespace PROKARYOTIC
{
	std::shared_ptr<spdlog::logger>  Log::s_corelogger;
	std::shared_ptr<spdlog::logger>  Log::s_clientlogger;

	void Log::init() 
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_corelogger = spdlog::stdout_color_mt("PROKARYOTIC");
		s_corelogger->set_level(spdlog::level::trace);

		s_clientlogger = spdlog::stdout_color_mt("APP");
		s_clientlogger->set_level(spdlog::level::trace);
	}

}
