// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once
#include <string_view>

namespace FredEmmott::CompressedEmbed {
struct StoredResource {
  std::string_view mName;
  std::size_t mOffset {};
  std::size_t mSize {};
};

}