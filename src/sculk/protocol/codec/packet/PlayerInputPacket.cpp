// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerInputPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PlayerInputPacket::getId() const noexcept { return MinecraftPacketIds::PlayerInput_Deprecated; }

std::string_view PlayerInputPacket::getName() const noexcept { return "PlayerInputPacket"; }

void PlayerInputPacket::write(BinaryStream& stream) const {
    mMove.write(stream);
    stream.writeBool(mJumping);
    stream.writeBool(mSneaking);
}

Result<> PlayerInputPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mMove.read(stream));
    _SCULK_READ(stream.readBool(mJumping));
    return stream.readBool(mSneaking);
}

std::string PlayerInputPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mMove)); }

} // namespace sculk::protocol::inline abi_v975
