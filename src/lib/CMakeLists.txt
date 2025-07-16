add_library(
  compressed-embed
  # <type> = BUILD_SHARED_LIBS ? SHARED : STATIC
  FredEmmott/CompressedEmbed/Win32Backend.cpp
)
target_sources(
  compressed-embed
  PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  FILES
  FredEmmott/CompressedEmbed/Backend.hpp
  FredEmmott/CompressedEmbed/InputResource.hpp
  FredEmmott/CompressedEmbed/StoredResource.hpp
  FredEmmott/CompressedEmbed/StoredResources.hpp
  FredEmmott/CompressedEmbed/Win32Backend.hpp
)
target_compile_definitions(compressed-embed PRIVATE COMPRESSED_EMBED_INTERNAL)
target_compile_features(compressed-embed PUBLIC cxx_std_23)
set_target_properties(compressed-embed PROPERTIES EXPORT_NAME runtime)
install(
  TARGETS compressed-embed
  EXPORT exports
  LIBRARY ARCHIVE FILE_SET HEADERS
)

if (PROJECT_IS_TOP_LEVEL)
  return()
endif ()
add_library(compressed-embed::runtime ALIAS compressed-embed)