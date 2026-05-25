// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MultiplayerSettingsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds MultiplayerSettingsPacket::getId() const noexcept { return MinecraftPacketIds::MultiplayerSettings; }

std::string_view MultiplayerSettingsPacket::getName() const noexcept { return "MultiplayerSettingsPacket"; }

void MultiplayerSettingsPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeVarInt);
}

Result<> MultiplayerSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mType, &ReadOnlyBinaryStream::readVarInt);
}

std::string MultiplayerSettingsPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mType)); }

} // namespace sculk::protocol::inline abi_v975
