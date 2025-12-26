function(add_compressed_embed_library TARGET)
  if (TARGET compressed-embed::compressor)
    set(COMPRESSED_EMBED_EXE compressed-embed::compressor)
  else ()
    find_program(COMPRESSED_EMBED_EXE compressed-embed REQUIRED)
  endif ()
  set(options WITHOUT_SINGLETON)
  set(oneValueArgs OUTPUT_CPP OUTPUT_HPP INTERMEDIATE_JSON_FILE NAMESPACE CLASSNAME)
  set(multiValueArgs INPUTS)
  cmake_parse_arguments(arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(JSON "{}")
  string(JSON JSON SET "${JSON}" "output_class_name" "\"${arg_CLASSNAME}\"")
  string(JSON JSON SET "${JSON}" "output_cpp_file" "\"${arg_OUTPUT_CPP}\"")
  string(JSON JSON SET "${JSON}" "output_hpp_file" "\"${arg_OUTPUT_HPP}\"")
  if (arg_WITHOUT_SINGLETON)
    string(JSON JSON SET "${JSON}" "include_singleton" "false")
  endif()
  if (arg_NAMESPACE)
    string(JSON JSON SET "${JSON}" "output_namespace" "\"${arg_NAMESPACE}\"")
  endif ()

  set(INPUTS_JSON "{}")
  set(INPUT_FILES)
  while (arg_INPUTS)
    list(POP_FRONT arg_INPUTS KEY PATH)
    cmake_path(
      ABSOLUTE_PATH
      PATH
      BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      NORMALIZE
    )
    list(APPEND INPUT_FILES "${PATH}")
    string(JSON INPUTS_JSON SET "${INPUTS_JSON}" "${KEY}" "\"${PATH}\"")
  endwhile ()
  string(JSON JSON SET "${JSON}" "input_files" "${INPUTS_JSON}")

  if (NOT arg_INTERMEDIATE_JSON_FILE)
    cmake_path(
      REPLACE_EXTENSION
      arg_OUTPUT_CPP
      LAST_ONLY
      compressed-embed.json
      OUTPUT_VARIABLE arg_INTERMEDIATE_JSON_FILE
    )
  endif ()
  file(WRITE "${arg_INTERMEDIATE_JSON_FILE}" "${JSON}")
  add_custom_command(
    OUTPUT "${arg_OUTPUT_CPP}" "${arg_OUTPUT_HPP}"
    MAIN_DEPENDENCY "${arg_INTERMEDIATE_JSON_FILE}"
    DEPENDS
    "${arg_INTERMEDIATE_JSON_FILE}"
    "${INPUT_FILES}"
    "${COMPRESSED_EMBED_EXE}"
    VERBATIM
    CODEGEN
    COMMAND
    "${COMPRESSED_EMBED_EXE}" "${arg_INTERMEDIATE_JSON_FILE}"
  )
  add_library("${TARGET}" OBJECT "${arg_OUTPUT_CPP}" "${arg_OUTPUT_HPP}")
  target_link_libraries("${TARGET}" PUBLIC compressed-embed::runtime)
  target_compile_features("${TARGET}" PUBLIC cxx_std_23)
endfunction()
