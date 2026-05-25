// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerActionPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PlayerActionPacket::getId() const noexcept { return MinecraftPacketIds::PlayerAction; }

std::string_view PlayerActionPacket::getName() const noexcept { return "PlayerActionPacket"; }

void PlayerActionPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mPlayerRuntimeId);
    stream.writeEnum(mAction, &BinaryStream::writeVarInt);
    mBlockPosition.write(stream);
    mResultPosition.write(stream);
    stream.writeVarInt(mFace);
}

Result<> PlayerActionPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mPlayerRuntimeId));
    _SCULK_READ(stream.readEnum(mAction, &ReadOnlyBinaryStream::readVarInt));
    _SCULK_READ(mBlockPosition.read(stream));
    _SCULK_READ(mResultPosition.read(stream));
    return stream.readVarInt(mFace);
}

std::string PlayerActionPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mPlayerRuntimeId),
        SCULK_FORMAT_FIELD(mAction),
        SCULK_FORMAT_FIELD(mBlockPosition),
        SCULK_FORMAT_FIELD(mResultPosition),
        SCULK_FORMAT_FIELD(mFace)
    );
}

} // namespace sculk::protocol::inline abi_v975
