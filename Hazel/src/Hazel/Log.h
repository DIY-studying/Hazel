#pragma once

#include "hzpch.h"
#include "Core.h"
#include<spdlog/spdlog.h>
#include"spdlog/fmt/ostr.h"

namespace Hazel
{
	class HAZEL_API Log
	{
	public:	
		static void Init();
		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } 
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
#define HZ_CORE_ERROR(...)	::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__);
#define HZ_CORE_WARN(...)	::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define HZ_CORE_INFO(...)		::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__);
#define HZ_CORE_TRACE(...)	::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__);

#define HZ_ERROR(...)	::Hazel::Log::GetClientLogger()->error(__VA_ARGS__);
#define HZ_WARN(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__);
#define HZ_INFO(...)		::Hazel::Log::GetClientLogger()->info(__VA_ARGS__);
#define HZ_TRACE(...)		::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__);

