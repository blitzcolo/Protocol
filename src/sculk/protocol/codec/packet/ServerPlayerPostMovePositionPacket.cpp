// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerPlayerPostMovePositionPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ServerPlayerPostMovePositionPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerPlayerPostMovePosition;
}

std::string_view ServerPlayerPostMovePositionPacket::getName() const noexcept {
    return "ServerPlayerPostMovePositionPacket";
}

void ServerPlayerPostMovePositionPacket::write(BinaryStream& stream) const { mPos.write(stream); }

Result<> ServerPlayerPostMovePositionPacket::read(ReadOnlyBinaryStream& stream) { return mPos.read(stream); }

std::string ServerPlayerPostMovePositionPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mPos));
}

} // namespace sculk::protocol::inline abi_v975
