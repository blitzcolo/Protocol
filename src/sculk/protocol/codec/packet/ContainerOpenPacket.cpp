// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ContainerOpenPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ContainerOpenPacket::getId() const noexcept { return MinecraftPacketIds::ContainerOpen; }

std::string_view ContainerOpenPacket::getName() const noexcept { return "ContainerOpenPacket"; }

void ContainerOpenPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mContainerId, &BinaryStream::writeByte);
    stream.writeEnum(mContainerType, &BinaryStream::writeByte);
    mPosition.write(stream);
    stream.writeVarInt64(mTargetActorId);
}

Result<> ContainerOpenPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mContainerId, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readEnum(mContainerType, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(mPosition.read(stream));
    return stream.readVarInt64(mTargetActorId);
}

std::string ContainerOpenPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mContainerId),
        SCULK_FORMAT_FIELD(mContainerType),
        SCULK_FORMAT_FIELD(mPosition),
        SCULK_FORMAT_FIELD(mTargetActorId)
    );
}

} // namespace sculk::protocol::inline abi_v975
