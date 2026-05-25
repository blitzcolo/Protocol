// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/EduUriResourcePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds EduUriResourcePacket::getId() const noexcept { return MinecraftPacketIds::EduUriResource; }

std::string_view EduUriResourcePacket::getName() const noexcept { return "EduUriResourcePacket"; }

void EduUriResourcePacket::write(BinaryStream& stream) const {
    stream.writeString(mButtonName);
    stream.writeString(mLinkUri);
}

Result<> EduUriResourcePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mButtonName));
    return stream.readString(mLinkUri);
}

std::string EduUriResourcePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mButtonName), SCULK_FORMAT_FIELD(mLinkUri));
}

} // namespace sculk::protocol::inline abi_v975
