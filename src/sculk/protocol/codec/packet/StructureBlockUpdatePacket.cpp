// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/StructureBlockUpdatePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds StructureBlockUpdatePacket::getId() const noexcept {
    return MinecraftPacketIds::StructureBlockUpdate;
}

std::string_view StructureBlockUpdatePacket::getName() const noexcept { return "StructureBlockUpdatePacket"; }

void StructureBlockUpdatePacket::write(BinaryStream& stream) const {
    mBlockPosition.write(stream);
    mStructureData.write(stream);
    stream.writeBool(mTrigger);
    stream.writeBool(mIsWaterLogged);
}

Result<> StructureBlockUpdatePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mBlockPosition.read(stream));
    _SCULK_READ(mStructureData.read(stream));
    _SCULK_READ(stream.readBool(mTrigger));
    return stream.readBool(mIsWaterLogged);
}

std::string StructureBlockUpdatePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mBlockPosition), SCULK_FORMAT_FIELD(mStructureData));
}

} // namespace sculk::protocol::inline abi_v975
