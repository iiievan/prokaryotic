#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace PROKARYOTIC
{
	class PRKRTC_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_corelogger; }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_clientlogger; }
	private:
		static std::shared_ptr<spdlog::logger>  s_corelogger;
		static std::shared_ptr<spdlog::logger>  s_clientlogger;
	};
}

#define LOG_CORE_ERR(...)		::PROKARYOTIC::Log::get_core_logger()->error(__VA_ARGS__)
#define LOG_CORE_WARN(...)		::PROKARYOTIC::Log::get_core_logger()->warn(__VA_ARGS__)
#define LOG_CORE_INFO(...)		::PROKARYOTIC::Log::get_core_logger()->info(__VA_ARGS__)
#define LOG_CORE_TRACE(...)		::PROKARYOTIC::Log::get_core_logger()->trace(__VA_ARGS__)
#define LOG_CORE_FATAL(...)		::PROKARYOTIC::Log::get_core_logger()->fatal(__VA_ARGS__)

#define LOG_CLIENT_ERR(...)		::PROKARYOTIC::Log::get_client_logger()->error(__VA_ARGS__)
#define LOG_CLIENT_WARN(...)	::PROKARYOTIC::Log::get_client_logger()->warn(__VA_ARGS__)
#define LOG_CLIENT_INFO(...)	::PROKARYOTIC::Log::get_client_logger()->info(__VA_ARGS__)
#define LOG_CLIENT_TRACE(...)	::PROKARYOTIC::Log::get_client_logger()->trace(__VA_ARGS__)
#define LOG_CLIENT_FATAL(...)	::PROKARYOTIC::Log::get_client_logger()->fatal(__VA_ARGS__)

