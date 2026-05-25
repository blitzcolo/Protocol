// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientCacheStatusPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientCacheStatusPacket::getId() const noexcept { return MinecraftPacketIds::ClientCacheStatus; }

std::string_view ClientCacheStatusPacket::getName() const noexcept { return "ClientCacheStatusPacket"; }

void ClientCacheStatusPacket::write(BinaryStream& stream) const { stream.writeBool(mIsCacheSupport); }

Result<> ClientCacheStatusPacket::read(ReadOnlyBinaryStream& stream) { return stream.readBool(mIsCacheSupport); }

std::string ClientCacheStatusPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mIsCacheSupport));
}

} // namespace sculk::protocol::inline abi_v975
