// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundDataDrivenUIShowScreenPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientboundDataDrivenUIShowScreenPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundDataDrivenUIShowScreen;
}

std::string_view ClientboundDataDrivenUIShowScreenPacket::getName() const noexcept {
    return "ClientboundDataDrivenUIShowScreenPacket";
}

void ClientboundDataDrivenUIShowScreenPacket::write(BinaryStream& stream) const {
    stream.writeString(mScreenId);
    stream.writeUnsignedInt(mFormId);
    stream.writeOptional(mDataInstanceId, &BinaryStream::writeUnsignedInt);
}

Result<> ClientboundDataDrivenUIShowScreenPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mScreenId));
    _SCULK_READ(stream.readUnsignedInt(mFormId));
    return stream.readOptional(mDataInstanceId, &ReadOnlyBinaryStream::readUnsignedInt);
}

std::string ClientboundDataDrivenUIShowScreenPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mScreenId),
        SCULK_FORMAT_FIELD(mFormId),
        SCULK_FORMAT_FIELD(mDataInstanceId)
    );
}

} // namespace sculk::protocol::inline abi_v975
