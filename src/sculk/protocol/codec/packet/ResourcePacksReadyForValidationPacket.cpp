// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePacksReadyForValidationPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ResourcePacksReadyForValidationPacket::getId() const noexcept {
    return MinecraftPacketIds::ResourcePacksReadyForValidation;
}

std::string_view ResourcePacksReadyForValidationPacket::getName() const noexcept {
    return "ResourcePacksReadyForValidationPacket";
}

void ResourcePacksReadyForValidationPacket::write(BinaryStream&) const {}

Result<> ResourcePacksReadyForValidationPacket::read(ReadOnlyBinaryStream&) { return {}; }

std::string ResourcePacksReadyForValidationPacket::toString() const { return SCULK_FORMAT_PACKET(); }

} // namespace sculk::protocol::inline abi_v975
