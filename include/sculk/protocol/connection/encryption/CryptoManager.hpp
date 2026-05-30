// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace sculk::protocol::inline abi_v975 {

class CryptoManager {
public:
    CryptoManager();
    explicit CryptoManager(std::vector<std::byte> saltBytes);
    ~CryptoManager();

    CryptoManager(const CryptoManager&)            = delete;
    CryptoManager& operator=(const CryptoManager&) = delete;
    CryptoManager(CryptoManager&&) noexcept;
    CryptoManager& operator=(CryptoManager&&) noexcept;

    void setSalt(std::vector<std::byte> saltBytes);

    std::vector<std::byte> encrypt(const std::vector<std::byte>& bytes);
    std::vector<std::byte> decrypt(const std::vector<std::byte>& bytes);

    bool verify(const std::vector<std::byte>& bytes);

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace sculk::protocol::inline abi_v975