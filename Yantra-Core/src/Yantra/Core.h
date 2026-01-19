#pragma once
#include "yqpch.h"

// Standard Primitive Types
namespace Yantra{

    // Unsigned ints
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    // Signed ints

    using int8  = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
}

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
    #error "Linux is not supported yet!"
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
#else
        #error Yantra only supports Windows for now!
#endif

#define BIT(x) (1 << x)

// Assertion
#ifdef YANTRA_ENABLE_ASSERTS
	#define YANTRA_ASSERT(x, ...) { if(!(x)) { YANTRA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define YANTRA_CORE_ASSERT(x, ...) { if(!(x)) { YANTRA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define YANTRA_ASSERT(x, ...)
	#define YANTRA_CORE_ASSERT(x, ...)
#endif