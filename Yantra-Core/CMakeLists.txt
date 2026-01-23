cmake_minimum_required(VERSION 3.16)
project(Yantra-Core)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/spdlog)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
 "src/*.cpp" "src/*.h"
 "vendor/GLAD/src/glad.c"
 "vendor/imgui/imgui.cpp"
 "vendor/imgui/imgui_demo.cpp"
 "vendor/imgui/imgui_draw.cpp"
 "vendor/imgui/imgui_tables.cpp"
 "vendor/imgui/imgui_widgets.cpp"
 "vendor/imgui/backends/imgui_impl_glfw.cpp"
 "vendor/imgui/backends/imgui_impl_opengl3.cpp"
 )

add_library(Yantra-Core SHARED ${SOURCES})

set_source_files_properties(vendor/GLAD/src/glad.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


target_precompile_headers(Yantra-Core PRIVATE src/yqpch.h)

target_include_directories(Yantra-Core PUBLIC 
    src
    vendor/spdlog/include
    vendor/GLAD/include
    vendor/imgui
    vendor/GLM
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
    GLFW_INCLUDE_NONE
)

target_link_libraries(Yantra-Core PRIVATE glfw OpenGL::GL)
target_link_libraries(Yantra-Core PUBLIC spdlog)

if(MSVC)
        target_compile_options(Yantra-Core PRIVATE /wd4251)
endif()
