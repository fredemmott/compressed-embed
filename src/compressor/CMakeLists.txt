find_package(glaze CONFIG REQUIRED)

add_executable(
  compressor
  Config.hpp
  main.cpp)
target_link_libraries(compressor PRIVATE compressed-embed glaze::glaze)
set_target_properties(
  compressor
  PROPERTIES
  OUTPUT_NAME compressed-embed
)

if (PROJECT_IS_TOP_LEVEL)
  return()
endif ()
add_executable(compressed-embed::compressor ALIAS compressor)
set(
  COMPRESSED_EMBED_EXE
  "$<TARGET_FILE:compressed-embed::compressor>"
  CACHE STRING "Full path to compressed-embed executable"
)