// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/EmotePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds EmotePacket::getId() const noexcept { return MinecraftPacketIds::Emote; }

std::string_view EmotePacket::getName() const noexcept { return "EmotePacket"; }

void EmotePacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeString(mEmoteId);
    stream.writeUnsignedVarInt(mEmoteLengthTicks);
    stream.writeString(mXuid);
    stream.writeString(mPlatformId);
    stream.writeByte(mFlags);
}

Result<> EmotePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(stream.readString(mEmoteId));
    _SCULK_READ(stream.readUnsignedVarInt(mEmoteLengthTicks));
    _SCULK_READ(stream.readString(mXuid));
    _SCULK_READ(stream.readString(mPlatformId));
    return stream.readByte(mFlags);
}

std::string EmotePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mActorRuntimeId),
        SCULK_FORMAT_FIELD(mEmoteId),
        SCULK_FORMAT_FIELD(mEmoteLengthTicks),
        SCULK_FORMAT_FIELD(mXuid),
        SCULK_FORMAT_FIELD(mPlatformId),
        SCULK_FORMAT_FIELD(mFlags)
    );
}

} // namespace sculk::protocol::inline abi_v975
