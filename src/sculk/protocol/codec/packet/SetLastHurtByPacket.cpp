// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetLastHurtByPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetLastHurtByPacket::getId() const noexcept { return MinecraftPacketIds::SetLastHurtBy; }

std::string_view SetLastHurtByPacket::getName() const noexcept { return "SetLastHurtByPacket"; }

void SetLastHurtByPacket::write(BinaryStream& stream) const { stream.writeVarInt(mLastHurtBy); }

Result<> SetLastHurtByPacket::read(ReadOnlyBinaryStream& stream) { return stream.readVarInt(mLastHurtBy); }

std::string SetLastHurtByPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mLastHurtBy)); }

} // namespace sculk::protocol::inline abi_v975
