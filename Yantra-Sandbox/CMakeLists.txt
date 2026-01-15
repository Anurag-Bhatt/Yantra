project(Yantra-Sandbox)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(Yantra-Sandbox ${SOURCES})

target_link_directories(Yantra-Sandbox PRIVATE Yantra-Core)