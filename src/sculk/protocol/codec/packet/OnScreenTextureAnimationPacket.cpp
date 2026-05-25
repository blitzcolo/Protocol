// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/OnScreenTextureAnimationPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds OnScreenTextureAnimationPacket::getId() const noexcept {
    return MinecraftPacketIds::OnScreenTextureAnimation;
}

std::string_view OnScreenTextureAnimationPacket::getName() const noexcept { return "OnScreenTextureAnimationPacket"; }

void OnScreenTextureAnimationPacket::write(BinaryStream& stream) const { stream.writeUnsignedInt(mEffectId); }

Result<> OnScreenTextureAnimationPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readUnsignedInt(mEffectId);
}

std::string OnScreenTextureAnimationPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mEffectId));
}

} // namespace sculk::protocol::inline abi_v975
