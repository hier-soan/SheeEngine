#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#define SENGINE_LOG_INFO(...)	     SheeEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SENGINE_LOG_WARN(...)		 SheeEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SENGINE_LOG_ERROR(...)	     SheeEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SENGINE_LOG_FATAL(...)	     SheeEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define APPLICATION_LOG_INFO(...)	 SheeEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define APPLICATION_LOG_WARN(...)	 SheeEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APPLICATION_LOG_ERROR(...)	 SheeEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define APPLICATION_LOG_FATAL(...)	 SheeEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

namespace SheeEngine
{
	class SENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};
}


