// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NetworkStackLatencyPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds NetworkStackLatencyPacket::getId() const noexcept { return MinecraftPacketIds::NetworkStackLatency; }

std::string_view NetworkStackLatencyPacket::getName() const noexcept { return "NetworkStackLatencyPacket"; }

void NetworkStackLatencyPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedInt64(mCreationTime);
    stream.writeBool(mIsFromServer);
}

Result<> NetworkStackLatencyPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedInt64(mCreationTime));
    return stream.readBool(mIsFromServer);
}

std::string NetworkStackLatencyPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCreationTime), SCULK_FORMAT_FIELD(mIsFromServer));
}

} // namespace sculk::protocol::inline abi_v975
