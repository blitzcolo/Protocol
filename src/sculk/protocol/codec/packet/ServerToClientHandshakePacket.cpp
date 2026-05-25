// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerToClientHandshakePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ServerToClientHandshakePacket::getId() const noexcept {
    return MinecraftPacketIds::ServerToClientHandshake;
}

std::string_view ServerToClientHandshakePacket::getName() const noexcept { return "ServerToClientHandshakePacket"; }

void ServerToClientHandshakePacket::write(BinaryStream& stream) const { stream.writeString(mHandshakeWebToken); }

Result<> ServerToClientHandshakePacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readString(mHandshakeWebToken);
}

std::string ServerToClientHandshakePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mHandshakeWebToken));
}

} // namespace sculk::protocol::inline abi_v975
