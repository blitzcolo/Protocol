// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraSplinePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraSplinePacket::getId() const noexcept { return MinecraftPacketIds::CameraSpline; }

std::string_view CameraSplinePacket::getName() const noexcept { return "CameraSplinePacket"; }

void CameraSplinePacket::write(BinaryStream& stream) const {
    stream.writeArray(mCameraDataSplines, &CameraSplineDefinition::write);
}

Result<> CameraSplinePacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mCameraDataSplines, &CameraSplineDefinition::read);
}

std::string CameraSplinePacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCameraDataSplines)); }

} // namespace sculk::protocol::inline abi_v975
