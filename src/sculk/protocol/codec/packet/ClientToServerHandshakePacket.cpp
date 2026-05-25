// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientToServerHandshakePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientToServerHandshakePacket::getId() const noexcept {
    return MinecraftPacketIds::ClientToServerHandshake;
}

std::string_view ClientToServerHandshakePacket::getName() const noexcept { return "ClientToServerHandshakePacket"; }

void ClientToServerHandshakePacket::write(BinaryStream&) const {}

Result<> ClientToServerHandshakePacket::read(ReadOnlyBinaryStream&) { return {}; }

std::string ClientToServerHandshakePacket::toString() const { return SCULK_FORMAT_PACKET(); }

} // namespace sculk::protocol::inline abi_v975
