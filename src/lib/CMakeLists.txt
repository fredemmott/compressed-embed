if (WIN32 AND BUILD_SHARED_LIBS)
  set(COMPRESSED_EMBED_WIN32_DLL ON)
endif ()
set(CONFIG_HPP "${CMAKE_CURRENT_BINARY_DIR}/include/FredEmmott/CompressedEmbed/config.hpp")
configure_file(FredEmmott/CompressedEmbed/config.hpp.in "${CONFIG_HPP}")
add_library(
  compressed-embed
  # <type> = BUILD_SHARED_LIBS ? SHARED : STATIC
  FredEmmott/CompressedEmbed/Win32Backend.cpp
  "${CONFIG_HPP}"
)
target_sources(
  compressed-embed
  PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/include"
  FILES
  FredEmmott/CompressedEmbed/Backend.hpp
  FredEmmott/CompressedEmbed/InputResource.hpp
  FredEmmott/CompressedEmbed/StoredResource.hpp
  FredEmmott/CompressedEmbed/StoredResources.hpp
  FredEmmott/CompressedEmbed/Win32Backend.hpp
  "${CONFIG_HPP}"
)
target_compile_definitions(compressed-embed PRIVATE COMPRESSED_EMBED_INTERNAL)
target_compile_features(compressed-embed PUBLIC cxx_std_23)
set_target_properties(
  compressed-embed
  PROPERTIES
  EXPORT_NAME runtime
  DEBUG_POSTFIX "d"
)
install(
  TARGETS compressed-embed
  EXPORT exports
  LIBRARY ARCHIVE FILE_SET HEADERS
)

if (PROJECT_IS_TOP_LEVEL)
  return()
endif ()
add_library(compressed-embed::runtime ALIAS compressed-embed)