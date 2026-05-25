// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RemoveVolumeEntityPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds RemoveVolumeEntityPacket::getId() const noexcept { return MinecraftPacketIds::RemoveVolumeEntity; }

std::string_view RemoveVolumeEntityPacket::getName() const noexcept { return "RemoveVolumeEntityPacket"; }

void RemoveVolumeEntityPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mEntityNetId);
    stream.writeVarInt(mDimensionType);
}

Result<> RemoveVolumeEntityPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt(mEntityNetId));
    return stream.readVarInt(mDimensionType);
}

std::string RemoveVolumeEntityPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mEntityNetId), SCULK_FORMAT_FIELD(mDimensionType));
}

} // namespace sculk::protocol::inline abi_v975
