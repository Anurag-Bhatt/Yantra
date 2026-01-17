#pragma once

#include <Yantra/Core.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Yantra {

	class YANTRA_API Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// Core log macros
#define YANTRA_CORE_TRACE(...)			::Yantra::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YANTRA_CORE_INFO(...)			::Yantra::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YANTRA_CORE_WARN(...)			::Yantra::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YANTRA_CORE_ERROR(...)			::Yantra::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YANTRA_CORE_CRITICAL(...)			::Yantra::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define YANTRA_TRACE(...)				::Yantra::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YANTRA_INFO(...)				::Yantra::Log::GetClientLogger()->info(__VA_ARGS__)
#define YANTRA_WARN(...)				::Yantra::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YANTRA_ERROR(...)				::Yantra::Log::GetClientLogger()->error(__VA_ARGS__)
#define YANTRA_CRITICAL(...)				::Yantra::Log::GetClientLogger()->critical(__VA_ARGS__)
