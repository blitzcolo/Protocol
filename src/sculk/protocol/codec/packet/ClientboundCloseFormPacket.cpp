// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundCloseFormPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientboundCloseFormPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundCloseForm;
}

std::string_view ClientboundCloseFormPacket::getName() const noexcept { return "ClientboundCloseFormPacket"; }

void ClientboundCloseFormPacket::write(BinaryStream&) const {}

Result<> ClientboundCloseFormPacket::read(ReadOnlyBinaryStream&) { return {}; }

std::string ClientboundCloseFormPacket::toString() const { return SCULK_FORMAT_PACKET(); }

} // namespace sculk::protocol::inline abi_v975
