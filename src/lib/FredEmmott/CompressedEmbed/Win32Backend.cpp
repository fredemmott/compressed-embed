// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#include "Win32Backend.hpp"

#include <windows.h>

#include <algorithm>
#include <memory>
#include <print>
#include <stdexcept>

#include "compressapi.h"

#pragma comment(lib, "Cabinet.lib")

namespace FredEmmott::CompressedEmbed {

struct CompressorDeleter {
  static void operator()(const COMPRESSOR_HANDLE handle) {
    CloseCompressor(handle);
  }
};
struct DecompressorDeleter {
  static void operator()(const DECOMPRESSOR_HANDLE handle) {
    CloseDecompressor(handle);
  }
};
using unique_compressor = std::unique_ptr<
  std::remove_pointer_t<COMPRESSOR_HANDLE>, CompressorDeleter>;
using unique_decompressor = std::unique_ptr<
  std::remove_pointer_t<DECOMPRESSOR_HANDLE>, DecompressorDeleter>;

StoredResources BasicWin32Backend::compress(
  const DWORD algorithm, const std::span<InputResource> input) {
  StoredResources result;
  std::vector<std::byte> inputBlob;
  result.mUncompressedBufferSize
    = std::ranges::fold_left(input, 0, [](auto acc, const auto& resource) {
        return acc + resource.mData.size();
      });
  inputBlob.reserve(result.mUncompressedBufferSize);
  for (auto&& resource: input) {
    result.mResources.emplace_back(
      resource.mKey, inputBlob.size(), resource.mData.size());
    inputBlob.append_range(resource.mData);
  }

  unique_compressor compressor {};
  CreateCompressor(algorithm, nullptr, std::out_ptr(compressor));
  SIZE_T bufferSize {};
  Compress(
    compressor.get(),
    inputBlob.data(),
    inputBlob.size(),
    nullptr,
    0,
    &bufferSize);
  result.mCompressed.resize(bufferSize);
  SIZE_T compressedSize {};
  Compress(
    compressor.get(),
    inputBlob.data(),
    inputBlob.size(),
    result.mCompressed.data(),
    bufferSize,
    &compressedSize);
  result.mCompressed.resize(compressedSize);
  return result;
}

std::vector<std::byte> BasicWin32Backend::decompress(
  const DWORD algorithm, const std::span<const std::byte> compressed) {
  std::vector<std::byte> buffer;
  unique_decompressor decompressor {};
  CreateDecompressor(algorithm, nullptr, std::out_ptr(decompressor));
  SIZE_T bufferSize {};
  Decompress(
    decompressor.get(),
    compressed.data(),
    compressed.size(),
    nullptr,
    0,
    &bufferSize);
  buffer.resize(bufferSize);
  SIZE_T actualSize {};
  Decompress(
    decompressor.get(),
    compressed.data(),
    compressed.size(),
    buffer.data(),
    bufferSize,
    &actualSize);
  buffer.resize(actualSize);
  buffer.shrink_to_fit();
  return buffer;
}

}// namespace FredEmmott::CompressedEmbed
