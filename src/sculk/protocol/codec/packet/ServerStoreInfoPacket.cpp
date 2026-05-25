// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerStoreInfoPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ServerStoreInfoPacket::getId() const noexcept { return MinecraftPacketIds::ServerStoreInfo; }

std::string_view ServerStoreInfoPacket::getName() const noexcept { return "ServerStoreInfoPacket"; }

void ServerStoreInfoPacket::write(BinaryStream& stream) const {
    stream.writeString(mStoreId);
    stream.writeString(mStoreName);
}

Result<> ServerStoreInfoPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mStoreId));
    return stream.readString(mStoreName);
}

std::string ServerStoreInfoPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mStoreId), SCULK_FORMAT_FIELD(mStoreName));
}

} // namespace sculk::protocol::inline abi_v975
