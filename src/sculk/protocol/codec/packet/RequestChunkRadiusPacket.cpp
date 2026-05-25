// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RequestChunkRadiusPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds RequestChunkRadiusPacket::getId() const noexcept { return MinecraftPacketIds::RequestChunkRadius; }

std::string_view RequestChunkRadiusPacket::getName() const noexcept { return "RequestChunkRadiusPacket"; }

void RequestChunkRadiusPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mChunkRadius);
    stream.writeByte(mMaxChunkRadius);
}

Result<> RequestChunkRadiusPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt(mChunkRadius));
    return stream.readByte(mMaxChunkRadius);
}

std::string RequestChunkRadiusPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mChunkRadius), SCULK_FORMAT_FIELD(mMaxChunkRadius));
}

} // namespace sculk::protocol::inline abi_v975
