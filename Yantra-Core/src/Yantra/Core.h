#pragma once
#include "Base.h"
#include "Log.h"
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
