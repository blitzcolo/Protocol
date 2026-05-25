// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetTitlePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetTitlePacket::getId() const noexcept { return MinecraftPacketIds::SetTitle; }

std::string_view SetTitlePacket::getName() const noexcept { return "SetTitlePacket"; }

void SetTitlePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mTitleType, &BinaryStream::writeVarInt);
    stream.writeString(mTitleText);
    stream.writeVarInt(mFadeInTime);
    stream.writeVarInt(mStayTime);
    stream.writeVarInt(mFadeOutTime);
    stream.writeString(mXuid);
    stream.writeString(mPlatformId);
    stream.writeString(mFilteredMessage);
}

Result<> SetTitlePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mTitleType, &ReadOnlyBinaryStream::readVarInt));
    _SCULK_READ(stream.readString(mTitleText));
    _SCULK_READ(stream.readVarInt(mFadeInTime));
    _SCULK_READ(stream.readVarInt(mStayTime));
    _SCULK_READ(stream.readVarInt(mFadeOutTime));
    _SCULK_READ(stream.readString(mXuid));
    _SCULK_READ(stream.readString(mPlatformId));
    return stream.readString(mFilteredMessage);
}

std::string SetTitlePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mTitleType),
        SCULK_FORMAT_FIELD(mTitleText),
        SCULK_FORMAT_FIELD(mFadeInTime),
        SCULK_FORMAT_FIELD(mStayTime),
        SCULK_FORMAT_FIELD(mFadeOutTime),
        SCULK_FORMAT_FIELD(mXuid),
        SCULK_FORMAT_FIELD(mPlatformId),
        SCULK_FORMAT_FIELD(mFilteredMessage)
    );
}

} // namespace sculk::protocol::inline abi_v975
