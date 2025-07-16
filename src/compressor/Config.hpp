// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <glaze/glaze.hpp>

enum class Backend {
  Win32_LZMS,
  Win32_MSZIP,
};
template <>
struct glz::meta<Backend> {
  using enum Backend;
  static constexpr auto value = glz::enumerate(Win32_LZMS, Win32_MSZIP);
};

struct Config {
  Backend backend {Backend::Win32_MSZIP};

  std::string output_namespace;
  std::string output_class_name;
  std::string output_cpp_file;
  std::string output_hpp_file;

  std::unordered_map<std::string, std::string> input_files;
};
