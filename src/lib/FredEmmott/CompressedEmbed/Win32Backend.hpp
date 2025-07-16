// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <Windows.h>
#include <compressapi.h>

#include <span>

#include "InputResource.hpp"
#include "StoredResources.hpp"
#include "config.hpp"

namespace FredEmmott::CompressedEmbed {

struct BasicWin32Backend {
  static COMPRESSED_EMBED_API StoredResources
  compress(DWORD algorithm, std::span<InputResource> input);
  static COMPRESSED_EMBED_API std::vector<std::byte> decompress(
    DWORD algorithm, std::span<const std::byte> compressed);
};
template <DWORD Algorithm>
struct Win32Backend {
  static StoredResources compress(const std::span<InputResource> input) {
    return BasicWin32Backend::compress(Algorithm, input);
  }

  static std::vector<std::byte> decompress(
    const std::span<const std::byte> compressed) {
    return BasicWin32Backend::decompress(Algorithm, compressed);
  }
};

using Win32LZMSBackend = Win32Backend<COMPRESS_ALGORITHM_LZMS>;
using Win32MSZIPBackend = Win32Backend<COMPRESS_ALGORITHM_MSZIP>;

}// namespace FredEmmott::CompressedEmbed