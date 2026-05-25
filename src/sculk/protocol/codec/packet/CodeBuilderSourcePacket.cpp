// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CodeBuilderSourcePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CodeBuilderSourcePacket::getId() const noexcept { return MinecraftPacketIds::CodeBuilderSource; }

std::string_view CodeBuilderSourcePacket::getName() const noexcept { return "CodeBuilderSourcePacket"; }

void CodeBuilderSourcePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mOperation, &BinaryStream::writeByte);
    stream.writeEnum(mCategory, &BinaryStream::writeByte);
    stream.writeEnum(mCodeStatus, &BinaryStream::writeByte);
}

Result<> CodeBuilderSourcePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mOperation, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readEnum(mCategory, &ReadOnlyBinaryStream::readByte));
    return stream.readEnum(mCodeStatus, &ReadOnlyBinaryStream::readByte);
}

std::string CodeBuilderSourcePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mOperation),
        SCULK_FORMAT_FIELD(mCategory),
        SCULK_FORMAT_FIELD(mCodeStatus)
    );
}

} // namespace sculk::protocol::inline abi_v975
