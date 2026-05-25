// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateSubChunkBlocksPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds UpdateSubChunkBlocksPacket::getId() const noexcept {
    return MinecraftPacketIds::UpdateSubChunkBlocks;
}

std::string_view UpdateSubChunkBlocksPacket::getName() const noexcept { return "UpdateSubChunkBlocksPacket"; }

void UpdateSubChunkBlocksPacket::write(BinaryStream& stream) const {
    mSubChunkBlockPosition.write(stream);
    stream.writeArray(mBlocksChangeStandards, &SubChunkBlockChangeInfo::write);
    stream.writeArray(mBlocksChangeExtras, &SubChunkBlockChangeInfo::write);
}

Result<> UpdateSubChunkBlocksPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mSubChunkBlockPosition.read(stream));
    _SCULK_READ(stream.readArray(mBlocksChangeStandards, &SubChunkBlockChangeInfo::read));
    return stream.readArray(mBlocksChangeExtras, &SubChunkBlockChangeInfo::read);
}

std::string UpdateSubChunkBlocksPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mSubChunkBlockPosition),
        SCULK_FORMAT_FIELD(mBlocksChangeStandards),
        SCULK_FORMAT_FIELD(mBlocksChangeExtras)
    );
}

} // namespace sculk::protocol::inline abi_v975
