// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetHealthPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetHealthPacket::getId() const noexcept { return MinecraftPacketIds::SetHealth; }

std::string_view SetHealthPacket::getName() const noexcept { return "SetHealthPacket"; }

void SetHealthPacket::write(BinaryStream& stream) const { stream.writeVarInt(mHealth); }

Result<> SetHealthPacket::read(ReadOnlyBinaryStream& stream) { return stream.readVarInt(mHealth); }

std::string SetHealthPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mHealth)); }

} // namespace sculk::protocol::inline abi_v975
