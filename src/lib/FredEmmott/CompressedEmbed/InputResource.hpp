// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <string_view>

namespace FredEmmott::CompressedEmbed {

struct InputResource {
  std::string_view mKey;
  std::span<std::byte> mData;
};

}// namespace FredEmmott::CompressedEmbed