// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerboundLoadingScreenPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ServerboundLoadingScreenPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundLoadingScreen;
}

std::string_view ServerboundLoadingScreenPacket::getName() const noexcept { return "ServerboundLoadingScreenPacket"; }

void ServerboundLoadingScreenPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeVarInt);
    stream.writeOptional(mLoadingScreenId, &BinaryStream::writeUnsignedInt);
}

Result<> ServerboundLoadingScreenPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readVarInt));
    return stream.readOptional(mLoadingScreenId, &ReadOnlyBinaryStream::readUnsignedInt);
}

std::string ServerboundLoadingScreenPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mType), SCULK_FORMAT_FIELD(mLoadingScreenId));
}

} // namespace sculk::protocol::inline abi_v975
