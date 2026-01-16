#pragma once

#ifdef _WIN32
        #ifdef _WIN64
                #define YANTRA_PLATFORM_WINDOWS
        #else
                #error "x86 platforms not supported!"
        #endif
#else
        #error  "Unknown Platform!"
#endif

#ifdef  YANTRA_BUILD_DLL
        #ifdef YANTRA_CORE_BUILD
                #define YANTRA_API __declspec(dllexport)
        #else
                #define YANTRA_API __declspec(dllimport)
        #endif
#else
        #define YANTRA_API  
#endif