// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GameRulesChangedPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds GameRulesChangedPacket::getId() const noexcept { return MinecraftPacketIds::GameRulesChanged; }

std::string_view GameRulesChangedPacket::getName() const noexcept { return "GameRulesChangedPacket"; }

void GameRulesChangedPacket::write(BinaryStream& stream) const { stream.writeArray(mGameRules, &GameRuleData::write); }

Result<> GameRulesChangedPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mGameRules, &GameRuleData::read);
}

std::string GameRulesChangedPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mGameRules)); }

} // namespace sculk::protocol::inline abi_v975
