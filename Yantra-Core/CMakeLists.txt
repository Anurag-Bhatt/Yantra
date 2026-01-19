cmake_minimum_required(VERSION 3.16)
project(Yantra-Core)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/spdlog)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_library(Yantra-Core SHARED ${SOURCES})

target_precompile_headers(Yantra-Core PRIVATE src/yqpch.h)

target_include_directories(Yantra-Core PUBLIC 
    src
    vendor/spdlog/include
)

target_include_directories(Yantra-Core PRIVATE
    vendor/GLFW/include
)

target_compile_definitions(Yantra-Core PRIVATE
    YANTRA_BUILD_DLL
    _CRT_SECURE_NO_WARNINGS
)

target_compile_definitions(Yantra-Core PUBLIC
    YANTRA_DYNAMIC_LINK
    YANTRA_ENABLE_ASSERTS
)

target_link_libraries(Yantra-Core PRIVATE glfw opengl32)
target_link_libraries(Yantra-Core PUBLIC spdlog)

if(MSVC)
        target_compile_options(Yantra-Core PRIVATE /wd4251)
endif()