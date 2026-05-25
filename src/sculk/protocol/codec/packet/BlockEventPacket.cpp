// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/BlockEventPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds BlockEventPacket::getId() const noexcept { return MinecraftPacketIds::BlockEvent; }

std::string_view BlockEventPacket::getName() const noexcept { return "BlockEventPacket"; }

void BlockEventPacket::write(BinaryStream& stream) const {
    mBlockPosition.write(stream);
    stream.writeEnum(mEventType, &BinaryStream::writeVarInt);
    stream.writeVarInt(mEventValue);
}

Result<> BlockEventPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mBlockPosition.read(stream));
    _SCULK_READ(stream.readEnum(mEventType, &ReadOnlyBinaryStream::readVarInt));
    return stream.readVarInt(mEventValue);
}

std::string BlockEventPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mBlockPosition),
        SCULK_FORMAT_FIELD(mEventType),
        SCULK_FORMAT_FIELD(mEventValue)
    );
}

} // namespace sculk::protocol::inline abi_v975
