// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraAimAssistPresetsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraAimAssistPresetsPacket::getId() const noexcept {
    return MinecraftPacketIds::CameraAimAssistPresets;
}

std::string_view CameraAimAssistPresetsPacket::getName() const noexcept { return "CameraAimAssistPresetsPacket"; }

void CameraAimAssistPresetsPacket::write(BinaryStream& stream) const {
    stream.writeArray(mCatagory, &CameraAimAssistCategoryDefinition::write);
    stream.writeArray(mPreset, &CameraAimAssistPresetDefinition::write);
    stream.writeEnum(mOperation, &BinaryStream::writeByte);
}

Result<> CameraAimAssistPresetsPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mCatagory, &CameraAimAssistCategoryDefinition::read));
    _SCULK_READ(stream.readArray(mPreset, &CameraAimAssistPresetDefinition::read));
    return stream.readEnum(mOperation, &ReadOnlyBinaryStream::readByte);
}

std::string CameraAimAssistPresetsPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mCatagories),
        SCULK_FORMAT_FIELD(mPreset),
        SCULK_FORMAT_FIELD(mCatagory),
        SCULK_FORMAT_FIELD(mOperation)
    );
}

} // namespace sculk::protocol::inline abi_v975
