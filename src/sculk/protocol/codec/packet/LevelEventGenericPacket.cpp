// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LevelEventGenericPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds LevelEventGenericPacket::getId() const noexcept { return MinecraftPacketIds::LevelEventGeneric; }

std::string_view LevelEventGenericPacket::getName() const noexcept { return "LevelEventGenericPacket"; }

void LevelEventGenericPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mEventId);
    mData.serialize(stream);
}

Result<> LevelEventGenericPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt(mEventId));
    return mData.deserialize(stream);
}

std::string LevelEventGenericPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mEventId), SCULK_FORMAT_FIELD(mData));
}

} // namespace sculk::protocol::inline abi_v975
