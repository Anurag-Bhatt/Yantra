#pragma once

// Platform Detection
#ifdef _WIN32
    #ifdef _WIN64
        #define YANTRA_PLATFORM_WINDOWS
    #else
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define YANTRA_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define YANTRA_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple Platform!"
    #endif
#elif defined(__ANDROID__)
    #define YANTRA_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define YANTRA_PLATFORM_LINUX
#else
    #error "Unknown Platform!"
#endif

// DLL Support
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
    #if YANTRA_DYNAMIC_LINK
        #ifdef YANTRA_BUILD_DLL
            #define YANTRA_API __attribute__((visibility("default")))
        #else
            #define YANTRA_API
        #endif
    #else
        #define YANTRA_API
    #endif
#else
    #error "Yantra only supports Windows and Linux!"
#endif
