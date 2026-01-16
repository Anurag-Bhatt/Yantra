cmake_minimum_required(VERSION 3.12)
project(Yantra-Core)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_library(Yantra-Core STATIC ${SOURCES})

target_include_directories(Yantra-Core PUBLIC src)