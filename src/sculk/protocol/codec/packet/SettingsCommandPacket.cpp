// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SettingsCommandPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SettingsCommandPacket::getId() const noexcept { return MinecraftPacketIds::SettingsCommand; }

std::string_view SettingsCommandPacket::getName() const noexcept { return "SettingsCommandPacket"; }

void SettingsCommandPacket::write(BinaryStream& stream) const {
    stream.writeString(mCommand);
    stream.writeBool(mSuppressOutput);
}

Result<> SettingsCommandPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mCommand));
    return stream.readBool(mSuppressOutput);
}

std::string SettingsCommandPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCommand), SCULK_FORMAT_FIELD(mSuppressOutput));
}

} // namespace sculk::protocol::inline abi_v975
