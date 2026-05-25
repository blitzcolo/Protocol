// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NetworkSettingsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds NetworkSettingsPacket::getId() const noexcept { return MinecraftPacketIds::NetworkSettings; }

std::string_view NetworkSettingsPacket::getName() const noexcept { return "NetworkSettingsPacket"; }

void NetworkSettingsPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedShort(mCompressionThreshold);
    stream.writeEnum(mCompressionAlgorithm, &BinaryStream::writeSignedShort);
    stream.writeBool(mClientThrottleEnabled);
    stream.writeByte(mClientThrottleThreshold);
    stream.writeFloat(mClientThrottleScalar);
}

Result<> NetworkSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedShort(mCompressionThreshold));
    _SCULK_READ(stream.readEnum(mCompressionAlgorithm, &ReadOnlyBinaryStream::readSignedShort));
    _SCULK_READ(stream.readBool(mClientThrottleEnabled));
    _SCULK_READ(stream.readByte(mClientThrottleThreshold));
    return stream.readFloat(mClientThrottleScalar);
}

std::string NetworkSettingsPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mCompressionAlgorithm),
        SCULK_FORMAT_FIELD(mClientThrottleEnabled),
        SCULK_FORMAT_FIELD(mClientThrottleThreshold),
        SCULK_FORMAT_FIELD(mClientThrottleScalar)
    );
}

} // namespace sculk::protocol::inline abi_v975
