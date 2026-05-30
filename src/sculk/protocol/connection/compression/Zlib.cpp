// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/compression/Zlib.hpp"
#include "sculk/protocol/utility/Result.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <limits>
#include <zlib.h>

namespace sculk::protocol::inline abi_v975::compression::zlib {

namespace detail {

class ZlibStream final {
public:
    enum class Mode { None, Deflate, Inflate };

    z_stream stream{};
    Mode     mode = Mode::None;

    ZlibStream() {
        stream.zalloc    = Z_NULL;
        stream.zfree     = Z_NULL;
        stream.opaque    = Z_NULL;
        stream.next_in   = Z_NULL;
        stream.avail_in  = 0;
        stream.next_out  = Z_NULL;
        stream.avail_out = 0;
    }

    ~ZlibStream() {
        if (mode == Mode::Deflate) {
            ::deflateEnd(&stream);
        } else if (mode == Mode::Inflate) {
            ::inflateEnd(&stream);
        }
    }

    ZlibStream(const ZlibStream&)            = delete;
    ZlibStream& operator=(const ZlibStream&) = delete;
};

constexpr std::size_t kChunkSize     = 16u * 1024u;
constexpr std::size_t kMaxOutputSize = 64ull * 1024ull * 1024ull;

} // namespace detail

std::vector<std::byte> compress(const std::vector<std::byte>& data) {
    if (data.empty()) {
        return {};
    }

    detail::ZlibStream z{};
    if (::deflateInit(&z.stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return {};
    }
    z.mode = detail::ZlibStream::Mode::Deflate;

    std::vector<std::byte> output{};
    if (data.size() <= static_cast<std::size_t>(std::numeric_limits<uLong>::max())) {
        output.reserve(static_cast<std::size_t>(::deflateBound(&z.stream, static_cast<uLong>(data.size()))));
    }

    std::array<std::byte, detail::kChunkSize> outChunk{};
    std::size_t                               inputOffset = 0;

    for (;;) {
        if (z.stream.avail_in == 0 && inputOffset < data.size()) {
            const std::size_t remaining = data.size() - inputOffset;
            const auto chunkIn  = static_cast<uInt>(std::min<std::size_t>(remaining, std::numeric_limits<uInt>::max()));
            z.stream.next_in    = reinterpret_cast<Bytef*>(const_cast<std::byte*>(data.data() + inputOffset));
            z.stream.avail_in   = chunkIn;
            inputOffset        += static_cast<std::size_t>(chunkIn);
        }

        const int flush = (inputOffset == data.size() && z.stream.avail_in == 0) ? Z_FINISH : Z_NO_FLUSH;

        z.stream.next_out  = reinterpret_cast<Bytef*>(outChunk.data());
        z.stream.avail_out = static_cast<uInt>(outChunk.size());

        const int code = ::deflate(&z.stream, flush);
        if (code != Z_OK && code != Z_STREAM_END) {
            return {};
        }

        const auto produced = outChunk.size() - z.stream.avail_out;
        if (produced > 0) {
            const std::size_t oldSize = output.size();
            output.resize(oldSize + produced);
            std::memcpy(output.data() + oldSize, outChunk.data(), produced);
        }

        if (code == Z_STREAM_END) {
            break;
        }
    }

    return output;
}

Result<std::vector<std::byte>> decompress(const std::vector<std::byte>& data) {
    if (data.empty()) {
        return error_utils::makeError("zlib decompress failed: input is empty");
    }

    detail::ZlibStream z{};
    if (::inflateInit(&z.stream) != Z_OK) {
        return error_utils::makeError("zlib decompress failed: inflate init failed");
    }
    z.mode = detail::ZlibStream::Mode::Inflate;

    std::vector<std::byte> output{};
    const std::size_t      initialReserve = data.size() > (detail::kMaxOutputSize / 3)
                                              ? detail::kMaxOutputSize
                                              : std::max<std::size_t>(data.size() * 3, 256);
    output.reserve(initialReserve);

    std::array<std::byte, detail::kChunkSize> outChunk{};
    std::size_t                               inputOffset = 0;

    for (;;) {
        if (z.stream.avail_in == 0 && inputOffset < data.size()) {
            const std::size_t remaining = data.size() - inputOffset;
            const auto chunkIn  = static_cast<uInt>(std::min<std::size_t>(remaining, std::numeric_limits<uInt>::max()));
            z.stream.next_in    = reinterpret_cast<Bytef*>(const_cast<std::byte*>(data.data() + inputOffset));
            z.stream.avail_in   = chunkIn;
            inputOffset        += static_cast<std::size_t>(chunkIn);
        }

        z.stream.next_out  = reinterpret_cast<Bytef*>(outChunk.data());
        z.stream.avail_out = static_cast<uInt>(outChunk.size());

        const int  code     = ::inflate(&z.stream, Z_NO_FLUSH);
        const auto produced = outChunk.size() - z.stream.avail_out;
        if (produced > 0) {
            if (output.size() > detail::kMaxOutputSize - produced) {
                return error_utils::makeError("zlib decompress failed: output exceeds configured limit");
            }

            const std::size_t oldSize = output.size();
            output.resize(oldSize + produced);
            std::memcpy(output.data() + oldSize, outChunk.data(), produced);
        }

        if (code == Z_STREAM_END) {
            return output;
        }

        if (code == Z_OK) {
            if (produced == 0 && z.stream.avail_in == 0 && inputOffset == data.size()) {
                return error_utils::makeError("zlib decompress failed: stream ended unexpectedly");
            }

            continue;
        }

        if (code == Z_BUF_ERROR && inputOffset < data.size()) {
            continue;
        }

        return error_utils::makeError("zlib decompress failed");
    }
}

} // namespace sculk::protocol::inline abi_v975::compression::zlib