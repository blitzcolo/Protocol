// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetDefaultGameTypePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetDefaultGameTypePacket::getId() const noexcept { return MinecraftPacketIds::SetDefaultGameType; }

std::string_view SetDefaultGameTypePacket::getName() const noexcept { return "SetDefaultGameTypePacket"; }

void SetDefaultGameTypePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mDefaultGameType, &BinaryStream::writeVarInt);
}

Result<> SetDefaultGameTypePacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mDefaultGameType, &ReadOnlyBinaryStream::readVarInt);
}

std::string SetDefaultGameTypePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mDefaultGameType));
}

} // namespace sculk::protocol::inline abi_v975
