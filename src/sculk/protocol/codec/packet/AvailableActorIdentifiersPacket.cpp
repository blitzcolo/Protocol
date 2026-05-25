// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AvailableActorIdentifiersPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds AvailableActorIdentifiersPacket::getId() const noexcept {
    return MinecraftPacketIds::AvailableActorIdentifiers;
}

std::string_view AvailableActorIdentifiersPacket::getName() const noexcept { return "AvailableActorIdentifiersPacket"; }

void AvailableActorIdentifiersPacket::write(BinaryStream& stream) const { mTag.write(stream); }

Result<> AvailableActorIdentifiersPacket::read(ReadOnlyBinaryStream& stream) { return mTag.read(stream); }

std::string AvailableActorIdentifiersPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mTag)); }

} // namespace sculk::protocol::inline abi_v975
