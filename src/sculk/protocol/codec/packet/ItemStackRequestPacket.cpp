// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ItemStackRequestPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ItemStackRequestPacket::getId() const noexcept { return MinecraftPacketIds::ItemStackRequest; }

std::string_view ItemStackRequestPacket::getName() const noexcept { return "ItemStackRequestPacket"; }

void ItemStackRequestPacket::write(BinaryStream& stream) const { mRequest.write(stream); }

Result<> ItemStackRequestPacket::read(ReadOnlyBinaryStream& stream) { return mRequest.read(stream); }

std::string ItemStackRequestPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mRequest)); }

} // namespace sculk::protocol::inline abi_v975
