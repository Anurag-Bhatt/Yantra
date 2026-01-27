#pragma once
#include <cstdint>
#include <functional>
// Standard Primitive Types
namespace Yantra {

#define YANTRA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Unsigned ints
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

// Signed ints

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
} // namespace Yantra

/*
 *   Platform Detection
 *   _WIN32 is defined for both 32-bit and 64-bit environments
 */
#ifdef _WIN32
#ifdef _WIN64
#define YANTRA_PLATFORM_WINDOWS
#else
#error "Yantra only supports x64 Windows!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#error "MacOS is not supported yet!"
#elif defined(__linux__)
#define YANTRA_PLATFORM_LINUX
#else
#error "Unknown platform!"
#endif

#ifdef YANTRA_PLATFORM_WINDOWS
#if YANTRA_DYNAMIC_LINK
#ifdef YANTRA_BUILD_DLL
#define YANTRA_API __declspec(dllexport)
#else
#define YANTRA_API __declspec(dllimport)
#endif
#else
#define YANTRA_API
#endif
#elif defined(YANTRA_PLATFORM_LINUX)
#define YANTRA_API __attribute__((visibility("default")))
#else
#define YANTRA_API
#endif

#define BIT(x) (1 << x)

#ifdef YANTRA_PLATFORM_WINDOWS
#define YANTRA_DEBUGBREAK() __debugbreak()
#elif defined(YANTRA_PLATFORM_LINUX)
#include <signal.h>
#define YANTRA_DEBUGBREAK() raise(SIGTRAP)
#else
#define YANTRA_DEBUGBREAK()
#endif

// Assertion
#ifdef YANTRA_ENABLE_ASSERTS
#define YANTRA_ASSERT(x, ...)                                                  \
  {                                                                            \
    if (!(x)) {                                                                \
      YANTRA_ERROR("Assertion Failed: {0}", __VA_ARGS__);                      \
      YANTRA_DEBUGBREAK();                                                     \
    }                                                                          \
  }
#define YANTRA_CORE_ASSERT(x, ...)                                             \
  {                                                                            \
    if (!(x)) {                                                                \
      YANTRA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                 \
      YANTRA_DEBUGBREAK();                                                     \
    }                                                                          \
  }
#else
#define YANTRA_ASSERT(x, ...)
#define YANTRA_CORE_ASSERT(x, ...)
#endif
