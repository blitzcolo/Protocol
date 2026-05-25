// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ChangeDimensionPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ChangeDimensionPacket::getId() const noexcept { return MinecraftPacketIds::ChangeDimension; }

std::string_view ChangeDimensionPacket::getName() const noexcept { return "ChangeDimensionPacket"; }

void ChangeDimensionPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mDimensionType);
    mPosition.write(stream);
    stream.writeBool(mRespawn);
    stream.writeOptional(mLoadingScreenId, &BinaryStream::writeUnsignedInt);
}

Result<> ChangeDimensionPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt(mDimensionType));
    _SCULK_READ(mPosition.read(stream));
    _SCULK_READ(stream.readBool(mRespawn));
    return stream.readOptional(mLoadingScreenId, &ReadOnlyBinaryStream::readUnsignedInt);
}

std::string ChangeDimensionPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mDimensionType),
        SCULK_FORMAT_FIELD(mPosition),
        SCULK_FORMAT_FIELD(mRespawn),
        SCULK_FORMAT_FIELD(mLoadingScreenId)
    );
}

} // namespace sculk::protocol::inline abi_v975
