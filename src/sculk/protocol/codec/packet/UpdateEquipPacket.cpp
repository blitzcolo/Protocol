// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateEquipPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds UpdateEquipPacket::getId() const noexcept { return MinecraftPacketIds::UpdateEquip; }

std::string_view UpdateEquipPacket::getName() const noexcept { return "UpdateEquipPacket"; }

void UpdateEquipPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mContainerId, &BinaryStream::writeByte);
    stream.writeEnum(mContainerType, &BinaryStream::writeByte);
    stream.writeVarInt(mSize);
    stream.writeVarInt64(mEntityUniqueId);
    mTag.write(stream);
}

Result<> UpdateEquipPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mContainerId, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readEnum(mContainerType, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readVarInt(mSize));
    _SCULK_READ(stream.readVarInt64(mEntityUniqueId));
    return mTag.read(stream);
}

std::string UpdateEquipPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mContainerId),
        SCULK_FORMAT_FIELD(mContainerType),
        SCULK_FORMAT_FIELD(mSize),
        SCULK_FORMAT_FIELD(mEntityUniqueId),
        SCULK_FORMAT_FIELD(mTag)
    );
}

} // namespace sculk::protocol::inline abi_v975
