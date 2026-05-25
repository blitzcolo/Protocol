// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MapCreateLockedCopyPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds MapCreateLockedCopyPacket::getId() const noexcept { return MinecraftPacketIds::MapCreateLockedCopy; }

std::string_view MapCreateLockedCopyPacket::getName() const noexcept { return "MapCreateLockedCopyPacket"; }

void MapCreateLockedCopyPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mOriginMapId);
    stream.writeVarInt64(mNewMapId);
}

Result<> MapCreateLockedCopyPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt64(mOriginMapId));
    return stream.readVarInt64(mNewMapId);
}

std::string MapCreateLockedCopyPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mOriginMapId), SCULK_FORMAT_FIELD(mNewMapId));
}

} // namespace sculk::protocol::inline abi_v975
