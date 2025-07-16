cmake_minimum_required(VERSION 3.31)

# Suppress unused variable warning
if (CMAKE_TOOLCHAIN_FILE)
  message(STATUS "Using toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif ()

project(compressed-embed LANGUAGES CXX)

add_subdirectory(src)
