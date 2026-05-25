// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraPresetsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraPresetsPacket::getId() const noexcept { return MinecraftPacketIds::CameraPresets; }

std::string_view CameraPresetsPacket::getName() const noexcept { return "CameraPresetsPacket"; }

void CameraPresetsPacket::write(BinaryStream& stream) const { stream.writeArray(mPresets, &CameraPreset::write); }

Result<> CameraPresetsPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mPresets, &CameraPreset::read);
}

std::string CameraPresetsPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mPresets)); }

} // namespace sculk::protocol::inline abi_v975
