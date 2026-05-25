// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CurrentStructureFeaturePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CurrentStructureFeaturePacket::getId() const noexcept {
    return MinecraftPacketIds::CurrentStructureFeature;
}

std::string_view CurrentStructureFeaturePacket::getName() const noexcept { return "CurrentStructureFeaturePacket"; }

void CurrentStructureFeaturePacket::write(BinaryStream& stream) const { stream.writeString(mCurrent); }

Result<> CurrentStructureFeaturePacket::read(ReadOnlyBinaryStream& stream) { return stream.readString(mCurrent); }

std::string CurrentStructureFeaturePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCurrent));
}

} // namespace sculk::protocol::inline abi_v975
