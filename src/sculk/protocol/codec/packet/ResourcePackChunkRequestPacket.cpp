// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePackChunkRequestPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ResourcePackChunkRequestPacket::getId() const noexcept {
    return MinecraftPacketIds::ResourcePackChunkRequest;
}

std::string_view ResourcePackChunkRequestPacket::getName() const noexcept { return "ResourcePackChunkRequestPacket"; }

void ResourcePackChunkRequestPacket::write(BinaryStream& stream) const {
    stream.writeString(mResourceName);
    stream.writeUnsignedInt(mChunkIndex);
}

Result<> ResourcePackChunkRequestPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mResourceName));
    return stream.readUnsignedInt(mChunkIndex);
}

std::string ResourcePackChunkRequestPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mResourceName), SCULK_FORMAT_FIELD(mChunkIndex));
}

} // namespace sculk::protocol::inline abi_v975
