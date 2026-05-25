// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePackChunkDataPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ResourcePackChunkDataPacket::getId() const noexcept {
    return MinecraftPacketIds::ResourcePackChunkData;
}

std::string_view ResourcePackChunkDataPacket::getName() const noexcept { return "ResourcePackChunkDataPacket"; }

void ResourcePackChunkDataPacket::write(BinaryStream& stream) const {
    stream.writeString(mResourceName);
    stream.writeUnsignedInt(mChunkIndex);
    stream.writeUnsignedInt64(mBytesOffset);
    stream.writeString(mChunkData);
}

Result<> ResourcePackChunkDataPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mResourceName));
    _SCULK_READ(stream.readUnsignedInt(mChunkIndex));
    _SCULK_READ(stream.readUnsignedInt64(mBytesOffset));
    return stream.readString(mChunkData);
}

std::string ResourcePackChunkDataPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mResourceName),
        SCULK_FORMAT_FIELD(mChunkIndex),
        SCULK_FORMAT_FIELD(mBytesOffset),
        SCULK_FORMAT_FIELD(mChunkData)
    );
}

} // namespace sculk::protocol::inline abi_v975
