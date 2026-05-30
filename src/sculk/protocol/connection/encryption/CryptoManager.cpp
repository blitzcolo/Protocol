// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/encryption/CryptoManager.hpp"
#include <algorithm>
#include <cstring>
#include <memory>
#include <openssl/evp.h>
#include <utility>
#include <vector>

namespace sculk::protocol::inline abi_v975 {

namespace {

constexpr std::size_t CHECKSUM_SIZE  = 8;
constexpr std::size_t AES_BLOCK_SIZE = 16;

struct EvpCipherCtxDeleter {
    void operator()(evp_cipher_ctx_st* ctx) const noexcept { EVP_CIPHER_CTX_free(ctx); }
};

using EvpCipherCtxPtr = std::unique_ptr<evp_cipher_ctx_st, EvpCipherCtxDeleter>;

struct EvpMdCtxDeleter {
    void operator()(EVP_MD_CTX* ctx) const noexcept { EVP_MD_CTX_free(ctx); }
};

using EvpMdCtxPtr = std::unique_ptr<EVP_MD_CTX, EvpMdCtxDeleter>;

void writeLittleEndian64(std::array<std::byte, 8>& out, std::uint64_t value) {
    for (std::size_t i = 0; i < out.size(); ++i) {
        out[i] = static_cast<std::byte>((value >> (i * 8U)) & 0xffU);
    }
}

const EVP_CIPHER* selectAesCtrCipher(std::size_t keySize) noexcept {
    switch (keySize) {
    case 16:
        return EVP_aes_128_ctr();
    case 24:
        return EVP_aes_192_ctr();
    case 32:
        return EVP_aes_256_ctr();
    default:
        return nullptr;
    }
}

std::array<std::byte, CHECKSUM_SIZE>
checksum(std::uint64_t counter, const std::byte* data, std::size_t dataSize, const std::vector<std::byte>& saltBytes) {
    std::array<std::byte, CHECKSUM_SIZE> counterBytes{};
    writeLittleEndian64(counterBytes, counter);

    std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
    unsigned int                               digestSize = 0;
    EvpMdCtxPtr                                ctx(EVP_MD_CTX_new());
    if (!ctx || EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1
        || EVP_DigestUpdate(ctx.get(), counterBytes.data(), counterBytes.size()) != 1
        || (dataSize != 0 && EVP_DigestUpdate(ctx.get(), data, dataSize) != 1)
        || (!saltBytes.empty() && EVP_DigestUpdate(ctx.get(), saltBytes.data(), saltBytes.size()) != 1)
        || EVP_DigestFinal_ex(ctx.get(), digest.data(), &digestSize) != 1 || digestSize < CHECKSUM_SIZE) {
        return {};
    }

    std::array<std::byte, CHECKSUM_SIZE> result{};
    std::memcpy(result.data(), digest.data(), result.size());
    return result;
}

bool initializeCipher(
    EvpCipherCtxPtr&                             ctx,
    bool                                         encrypt,
    const std::vector<std::byte>&                saltBytes,
    const std::array<std::byte, AES_BLOCK_SIZE>& initialCounterBlock
) {
    const EVP_CIPHER* cipher = selectAesCtrCipher(saltBytes.size());
    if (!cipher) {
        return false;
    }

    ctx.reset(EVP_CIPHER_CTX_new());
    return ctx != nullptr
        && EVP_CipherInit_ex(
               ctx.get(),
               cipher,
               nullptr,
               reinterpret_cast<const unsigned char*>(saltBytes.data()),
               reinterpret_cast<const unsigned char*>(initialCounterBlock.data()),
               encrypt ? 1 : 0
           ) == 1
        && EVP_CIPHER_CTX_set_padding(ctx.get(), 0) == 1;
}

std::vector<std::byte> ctrCrypt(EvpCipherCtxPtr& ctx, const std::vector<std::byte>& bytes) {
    if (bytes.empty()) {
        return {};
    }
    if (!ctx) {
        return bytes;
    }

    std::vector<std::byte> output(bytes.size());
    int                    outLen = 0;
    const bool             ok     = EVP_CipherUpdate(
                        ctx.get(),
                        reinterpret_cast<unsigned char*>(output.data()),
                        &outLen,
                        reinterpret_cast<const unsigned char*>(bytes.data()),
                        static_cast<int>(bytes.size())
                    )
                 == 1;

    if (!ok || static_cast<std::size_t>(outLen) != output.size()) {
        return bytes;
    }

    return output;
}

} // namespace

struct CryptoManager::Impl {
    std::uint64_t                         mEncryptCounter{};
    std::uint64_t                         mDecryptCounter{};
    std::vector<std::byte>                mSaltBytes{};
    std::array<std::byte, AES_BLOCK_SIZE> mInitialCounterBlock{};
    EvpCipherCtxPtr                       mEncryptCtx{};
    EvpCipherCtxPtr                       mDecryptCtx{};
};

CryptoManager::CryptoManager() : mImpl(std::make_unique<Impl>()) {}

CryptoManager::CryptoManager(std::vector<std::byte> saltBytes) : CryptoManager() { setSalt(std::move(saltBytes)); }

CryptoManager::~CryptoManager() = default;

CryptoManager::CryptoManager(CryptoManager&&) noexcept = default;

CryptoManager& CryptoManager::operator=(CryptoManager&&) noexcept = default;

void CryptoManager::setSalt(std::vector<std::byte> saltBytes) {
    mImpl->mSaltBytes      = std::move(saltBytes);
    mImpl->mEncryptCounter = 0;
    mImpl->mDecryptCounter = 0;
    mImpl->mEncryptCtx.reset();
    mImpl->mDecryptCtx.reset();
    mImpl->mInitialCounterBlock.fill(std::byte{});

    const std::size_t nonceSize = std::min<std::size_t>(mImpl->mSaltBytes.size(), 12);
    if (nonceSize != 0) {
        std::copy_n(mImpl->mSaltBytes.begin(), nonceSize, mImpl->mInitialCounterBlock.begin());
    }
    mImpl->mInitialCounterBlock[15] = std::byte{0x02};
}

std::vector<std::byte> CryptoManager::encrypt(const std::vector<std::byte>& bytes) {
    if (bytes.empty()) {
        return bytes;
    }

    std::vector<std::byte> data        = bytes;
    const std::byte*       payload     = data.data();
    const std::size_t      payloadSize = data.size();
    data.reserve(payloadSize + CHECKSUM_SIZE);
    const auto sum = checksum(mImpl->mEncryptCounter++, payload, payloadSize, mImpl->mSaltBytes);
    data.insert(data.end(), sum.begin(), sum.end());

    if (!mImpl->mEncryptCtx
        && !initializeCipher(mImpl->mEncryptCtx, true, mImpl->mSaltBytes, mImpl->mInitialCounterBlock)) {
        return bytes;
    }

    return ctrCrypt(mImpl->mEncryptCtx, data);
}

std::vector<std::byte> CryptoManager::decrypt(const std::vector<std::byte>& bytes) {
    if (bytes.empty()) {
        return bytes;
    }
    if (bytes.size() < CHECKSUM_SIZE) {
        return {};
    }

    if (!mImpl->mDecryptCtx
        && !initializeCipher(mImpl->mDecryptCtx, false, mImpl->mSaltBytes, mImpl->mInitialCounterBlock)) {
        return bytes;
    }

    auto clear = ctrCrypt(mImpl->mDecryptCtx, bytes);
    if (!verify(clear)) {
        return {};
    }

    clear.resize(clear.size() - CHECKSUM_SIZE);
    return clear;
}

bool CryptoManager::verify(const std::vector<std::byte>& bytes) {
    if (bytes.size() < CHECKSUM_SIZE) {
        return false;
    }

    const std::size_t payloadSize = bytes.size() - CHECKSUM_SIZE;
    const auto        expected    = checksum(mImpl->mDecryptCounter++, bytes.data(), payloadSize, mImpl->mSaltBytes);
    return std::equal(expected.begin(), expected.end(), bytes.begin() + static_cast<std::ptrdiff_t>(payloadSize));
}

} // namespace sculk::protocol::inline abi_v975