cmake_minimum_required(VERSION 3.12)
project(Yantra-Sandbox)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(Yantra-Sandbox ${SOURCES})

target_link_libraries(Yantra-Sandbox PRIVATE Yantra-Core)