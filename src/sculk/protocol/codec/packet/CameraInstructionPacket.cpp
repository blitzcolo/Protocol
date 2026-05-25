// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraInstructionPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraInstructionPacket::getId() const noexcept { return MinecraftPacketIds::CameraInstruction; }

std::string_view CameraInstructionPacket::getName() const noexcept { return "CameraInstructionPacket"; }

void CameraInstructionPacket::write(BinaryStream& stream) const { mCameraInstruction.write(stream); }

Result<> CameraInstructionPacket::read(ReadOnlyBinaryStream& stream) { return mCameraInstruction.read(stream); }

std::string CameraInstructionPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCameraInstruction));
}

} // namespace sculk::protocol::inline abi_v975
