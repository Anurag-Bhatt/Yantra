project(Yantra-Core)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(Yantra-Core STATIC ${SOURCES})

target_include_directories(Yantra-Core PUBLIC src)