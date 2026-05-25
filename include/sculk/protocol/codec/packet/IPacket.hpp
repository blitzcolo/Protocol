// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/MinecraftPacketIds.hpp"
#include "sculk/protocol/utility/BinaryStream.hpp"
#include "sculk/protocol/utility/ReadOnlyBinaryStream.hpp"
#include <format>

namespace sculk::protocol::inline abi_v975 {

class IPacket {
public:
    std::uint8_t mSenderSubClientId{};
    std::uint8_t mTargetSubClientId{};

public:
    IPacket() noexcept = default;

public:
    virtual ~IPacket() noexcept = default;

    [[nodiscard]] virtual MinecraftPacketIds getId() const noexcept = 0;

    [[nodiscard]] virtual std::string_view getName() const noexcept = 0;

    virtual void write(BinaryStream& stream) const = 0;

    [[nodiscard]] virtual Result<> read(ReadOnlyBinaryStream& stream) = 0;

    [[nodiscard]] virtual std::string toString() const { return std::string(getName()); }

    void writeHeader(BinaryStream& stream) const;

    [[nodiscard]] Result<> readHeader(ReadOnlyBinaryStream& stream);

    void writeWithHeader(BinaryStream& stream) const;

    [[nodiscard]] Result<> readWithHeader(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v975

template <>
struct std::formatter<sculk::protocol::abi_v975::IPacket> : std::formatter<std::string> {
    auto format(const sculk::protocol::abi_v975::IPacket& packet, format_context& ctx) const {
        return std::formatter<std::string>::format(packet.toString(), ctx);
    }
};

#if __has_include(<fmt/format.h>)
#include <fmt/format.h>
template <>
struct fmt::formatter<sculk::protocol::abi_v975::IPacket> : fmt::formatter<std::string> {
    auto format(const sculk::protocol::abi_v975::IPacket& packet, fmt::format_context& ctx) const {
        return fmt::formatter<std::string>::format(packet.toString(), ctx);
    }
};
#endif