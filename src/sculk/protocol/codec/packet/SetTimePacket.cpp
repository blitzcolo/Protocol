// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetTimePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetTimePacket::getId() const noexcept { return MinecraftPacketIds::SetTime; }

std::string_view SetTimePacket::getName() const noexcept { return "SetTimePacket"; }

void SetTimePacket::write(BinaryStream& stream) const { stream.writeVarInt(mTime); }

Result<> SetTimePacket::read(ReadOnlyBinaryStream& stream) { return stream.readVarInt(mTime); }

std::string SetTimePacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mTime)); }

} // namespace sculk::protocol::inline abi_v975
