// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateClientOptionsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds UpdateClientOptionsPacket::getId() const noexcept { return MinecraftPacketIds::UpdateClientOptions; }

std::string_view UpdateClientOptionsPacket::getName() const noexcept { return "UpdateClientOptionsPacket"; }

void UpdateClientOptionsPacket::write(BinaryStream& stream) const {
    stream.writeOptional(mGraphicsModeChange, [&](GraphicsMode mode) {
        stream.writeEnum(mode, &BinaryStream::writeByte);
    });
    stream.writeOptional(mFilterProfanity, &BinaryStream::writeBool);
}

Result<> UpdateClientOptionsPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readOptional(mGraphicsModeChange, [&](GraphicsMode& mode) {
        return stream.readEnum(mode, &ReadOnlyBinaryStream::readByte);
    }));
    return stream.readOptional(mFilterProfanity, &ReadOnlyBinaryStream::readBool);
}

std::string UpdateClientOptionsPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mGraphicsModeChange), SCULK_FORMAT_FIELD(mFilterProfanity));
}

} // namespace sculk::protocol::inline abi_v975
