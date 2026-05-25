// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetDifficultyPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetDifficultyPacket::getId() const noexcept { return MinecraftPacketIds::SetDifficulty; }

std::string_view SetDifficultyPacket::getName() const noexcept { return "SetDifficultyPacket"; }

void SetDifficultyPacket::write(BinaryStream& stream) const { stream.writeUnsignedVarInt(mDifficulty); }

Result<> SetDifficultyPacket::read(ReadOnlyBinaryStream& stream) { return stream.readUnsignedVarInt(mDifficulty); }

std::string SetDifficultyPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mDifficulty)); }

} // namespace sculk::protocol::inline abi_v975
