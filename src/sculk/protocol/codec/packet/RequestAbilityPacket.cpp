// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RequestAbilityPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds RequestAbilityPacket::getId() const noexcept { return MinecraftPacketIds::RequestAbility; }

std::string_view RequestAbilityPacket::getName() const noexcept { return "RequestAbilityPacket"; }

void RequestAbilityPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mAbility);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    if (mType != Type::Unset) {
        stream.writeBool(mBoolValue);
        stream.writeFloat(mFloatValue);
    }
}

Result<> RequestAbilityPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt(mAbility));
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readByte));
    if (mType != Type::Unset) {
        _SCULK_READ(stream.readBool(mBoolValue));
        _SCULK_READ(stream.readFloat(mFloatValue));
    }
    return {};
}

std::string RequestAbilityPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mAbility),
        SCULK_FORMAT_FIELD(mType),
        SCULK_FORMAT_FIELD(mBoolValue),
        SCULK_FORMAT_FIELD(mFloatValue)
    );
}

} // namespace sculk::protocol::inline abi_v975
