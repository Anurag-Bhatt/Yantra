cmake_minimum_required(VERSION 3.12)
project(Yantra-Sandbox)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(Yantra-Sandbox ${SOURCES})

target_link_libraries(Yantra-Sandbox PRIVATE Yantra-Core)

add_custom_command(TARGET Yantra-Sandbox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets
  ${CMAKE_BINARY_DIR}/bin/assets
  COMMENT "Copying assets to bin/assets..."
)

