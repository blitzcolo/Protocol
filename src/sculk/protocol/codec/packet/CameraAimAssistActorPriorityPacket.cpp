// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraAimAssistActorPriorityPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraAimAssistActorPriorityPacket::getId() const noexcept {
    return MinecraftPacketIds::CameraAimAssistActorPriority;
}

std::string_view CameraAimAssistActorPriorityPacket::getName() const noexcept {
    return "CameraAimAssistActorPriorityPacket";
}

void CameraAimAssistActorPriorityPacket::write(BinaryStream& stream) const {
    stream.writeArray(mCameraAimAssistActorPriorityList, &AimAssistActorPriorityData::write);
}

Result<> CameraAimAssistActorPriorityPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mCameraAimAssistActorPriorityList, &AimAssistActorPriorityData::read);
}

std::string CameraAimAssistActorPriorityPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCameraAimAssistActorPriorityList));
}

} // namespace sculk::protocol::inline abi_v975
