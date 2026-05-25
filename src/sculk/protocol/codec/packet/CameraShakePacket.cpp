// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraShakePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraShakePacket::getId() const noexcept { return MinecraftPacketIds::CameraShake; }

std::string_view CameraShakePacket::getName() const noexcept { return "CameraShakePacket"; }

void CameraShakePacket::write(BinaryStream& stream) const {
    stream.writeFloat(mIntensity);
    stream.writeFloat(mSeconds);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeEnum(mAction, &BinaryStream::writeByte);
}

Result<> CameraShakePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readFloat(mIntensity));
    _SCULK_READ(stream.readFloat(mSeconds));
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readByte));
    return stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte);
}

std::string CameraShakePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mIntensity),
        SCULK_FORMAT_FIELD(mSeconds),
        SCULK_FORMAT_FIELD(mType),
        SCULK_FORMAT_FIELD(mAction)
    );
}

} // namespace sculk::protocol::inline abi_v975
