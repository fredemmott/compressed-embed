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

add_executable(compressed-embed::compressor ALIAS compressor)