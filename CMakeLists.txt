cmake_minimum_required(VERSION 3.25..3.31)

# Suppress unused variable warning
if (CMAKE_TOOLCHAIN_FILE)
  message(STATUS "Using toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif ()

project(compressed-embed LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
if (NOT PROJECT_IS_TOP_LEVEL)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
endif ()

add_subdirectory(src)

install(
  FILES "${CMAKE_CURRENT_LIST_DIR}/cmake/CompressedEmbed.cmake"
  FILES "${CMAKE_CURRENT_LIST_DIR}/cmake/compressed-embed-config.cmake"
  DESTINATION "lib/cmake/compressed-embed"
)
install(
  EXPORT
  exports
  NAMESPACE "compressed-embed::"
  FILE compressed-embed-targets.cmake
  DESTINATION "lib/cmake/compressed-embed"
)