// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundDataStorePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientboundDataStorePacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundDataStore;
}

std::string_view ClientboundDataStorePacket::getName() const noexcept { return "ClientboundDataStorePacket"; }

void ClientboundDataStorePacket::write(BinaryStream& stream) const {
    mDataStoreUpdate.write(stream);
    mDataStoreChange.write(stream);
    mDataStoreRemoval.write(stream);
}

Result<> ClientboundDataStorePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mDataStoreUpdate.read(stream));
    _SCULK_READ(mDataStoreChange.read(stream));
    return mDataStoreRemoval.read(stream);
}

std::string ClientboundDataStorePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mDataStoreUpdate),
        SCULK_FORMAT_FIELD(mDataStoreChange),
        SCULK_FORMAT_FIELD(mDataStoreRemoval)
    );
}

} // namespace sculk::protocol::inline abi_v975
