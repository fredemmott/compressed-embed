// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once
#include <vector>

#include "StoredResource.hpp"

namespace FredEmmott::CompressedEmbed {

struct StoredResources {
  std::vector<std::byte> mCompressed;
  std::vector<StoredResource> mResources;
  std::size_t mUncompressedBufferSize {};
};

}// namespace FredEmmott::CompressedEmbed