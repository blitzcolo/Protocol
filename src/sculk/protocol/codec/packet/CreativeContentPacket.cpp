// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CreativeContentPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

void CreativeContentPacket::WriteEntry::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mNetId);
    mItem.write(stream);
    stream.writeUnsignedVarInt(mGroupIndex);
}

Result<> CreativeContentPacket::WriteEntry::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt(mNetId));
    _SCULK_READ(mItem.read(stream));
    return stream.readUnsignedVarInt(mGroupIndex);
}

void CreativeContentPacket::Group::write(BinaryStream& stream) const {
    stream.writeSignedInt(mCategory);
    stream.writeString(mName);
    mIcon.write(stream);
}

Result<> CreativeContentPacket::Group::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readSignedInt(mCategory));
    _SCULK_READ(stream.readString(mName));
    return mIcon.read(stream);
}

MinecraftPacketIds CreativeContentPacket::getId() const noexcept { return MinecraftPacketIds::CreativeContent; }

std::string_view CreativeContentPacket::getName() const noexcept { return "CreativeContentPacket"; }

void CreativeContentPacket::write(BinaryStream& stream) const {
    stream.writeArray(mGroups, &Group::write);
    stream.writeArray(mWriteEntries, &WriteEntry::write);
}

Result<> CreativeContentPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mGroups, &Group::read));
    return stream.readArray(mWriteEntries, &WriteEntry::read);
}

std::string CreativeContentPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mWriteEntries), SCULK_FORMAT_FIELD(mGroups));
}

} // namespace sculk::protocol::inline abi_v975
