// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MotionPredictionHintsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds MotionPredictionHintsPacket::getId() const noexcept {
    return MinecraftPacketIds::MotionPredictionHints;
}

std::string_view MotionPredictionHintsPacket::getName() const noexcept { return "MotionPredictionHintsPacket"; }

void MotionPredictionHintsPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    mMotion.write(stream);
    stream.writeBool(mOnGround);
}

Result<> MotionPredictionHintsPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(mMotion.read(stream));
    return stream.readBool(mOnGround);
}

std::string MotionPredictionHintsPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mActorRuntimeId),
        SCULK_FORMAT_FIELD(mMotion),
        SCULK_FORMAT_FIELD(mOnGround)
    );
}

} // namespace sculk::protocol::inline abi_v975
