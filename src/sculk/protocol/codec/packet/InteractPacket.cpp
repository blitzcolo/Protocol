// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/InteractPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds InteractPacket::getId() const noexcept { return MinecraftPacketIds::Interact; }

std::string_view InteractPacket::getName() const noexcept { return "InteractPacket"; }

void InteractPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeOptional(mPosition, &Vec3::write);
}

Result<> InteractPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    return stream.readOptional(mPosition, &Vec3::read);
}

std::string InteractPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mAction),
        SCULK_FORMAT_FIELD(mActorRuntimeId),
        SCULK_FORMAT_FIELD(mPosition)
    );
}

} // namespace sculk::protocol::inline abi_v975
