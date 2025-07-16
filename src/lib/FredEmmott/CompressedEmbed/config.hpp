// Copyright 2025 Fred Emmott <fred@fredemmott.com>
// SPDX-License-Identifier: MIT
#pragma once

#ifdef COMPRESSED_EMBED_INTERNAL
#define COMPRESSED_EMBED_API __declspec(dllexport)
#else
#define COMPRESSED_EMBED_API __declspec(dllimport)
#endif