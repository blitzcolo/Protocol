// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ToastRequestPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ToastRequestPacket::getId() const noexcept { return MinecraftPacketIds::ToastRequest; }

std::string_view ToastRequestPacket::getName() const noexcept { return "ToastRequestPacket"; }

void ToastRequestPacket::write(BinaryStream& stream) const {
    stream.writeString(mTitle);
    stream.writeString(mContent);
}

Result<> ToastRequestPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mTitle));
    return stream.readString(mContent);
}

std::string ToastRequestPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mTitle), SCULK_FORMAT_FIELD(mContent));
}

} // namespace sculk::protocol::inline abi_v975
