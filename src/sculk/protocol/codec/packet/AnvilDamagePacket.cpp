// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AnvilDamagePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds AnvilDamagePacket::getId() const noexcept { return MinecraftPacketIds::AnvilDamage; }

std::string_view AnvilDamagePacket::getName() const noexcept { return "AnvilDamagePacket"; }

void AnvilDamagePacket::write(BinaryStream& stream) const {
    stream.writeByte(mDamageAmount);
    mPosition.write(stream);
}

Result<> AnvilDamagePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readByte(mDamageAmount));
    return mPosition.read(stream);
}

std::string AnvilDamagePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mDamageAmount), SCULK_FORMAT_FIELD(mPosition));
}

} // namespace sculk::protocol::inline abi_v975
