// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/TickingAreasLoadStatusPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds TickingAreasLoadStatusPacket::getId() const noexcept {
    return MinecraftPacketIds::TickingAreasLoadStatus;
}

std::string_view TickingAreasLoadStatusPacket::getName() const noexcept { return "TickingAreasLoadStatusPacket"; }

void TickingAreasLoadStatusPacket::write(BinaryStream& stream) const { stream.writeBool(mWaitingForPreload); }

Result<> TickingAreasLoadStatusPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readBool(mWaitingForPreload);
}

std::string TickingAreasLoadStatusPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mWaitingForPreload));
}

} // namespace sculk::protocol::inline abi_v975
