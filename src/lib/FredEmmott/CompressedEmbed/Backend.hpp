// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <span>

#include "InputResource.hpp"
#include "StoredResources.hpp"

namespace FredEmmott::CompressedEmbed {

template <class T>
concept Backend = requires(
  std::span<InputResource> input, std::span<const std::byte> compressed) {
  T::compress(input);
  { T::compress(input) } -> std::convertible_to<StoredResources>;
  T::decompress(compressed);
  { T::decompress(compressed) } -> std::convertible_to<std::vector<std::byte>>;
};

}// namespace FredEmmott::CompressedEmbed