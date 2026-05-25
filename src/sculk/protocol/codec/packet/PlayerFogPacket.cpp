// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerFogPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PlayerFogPacket::getId() const noexcept { return MinecraftPacketIds::PlayerFog; }

std::string_view PlayerFogPacket::getName() const noexcept { return "PlayerFogPacket"; }

void PlayerFogPacket::write(BinaryStream& stream) const { stream.writeArray(mFogStack, &BinaryStream::writeString); }

Result<> PlayerFogPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mFogStack, &ReadOnlyBinaryStream::readString);
}

std::string PlayerFogPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mFogStack)); }

} // namespace sculk::protocol::inline abi_v975
