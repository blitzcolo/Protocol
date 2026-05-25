// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ItemRegistryPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ItemRegistryPacket::getId() const noexcept { return MinecraftPacketIds::ItemRegistry; }

std::string_view ItemRegistryPacket::getName() const noexcept { return "ItemRegistryPacket"; }

void ItemRegistryPacket::write(BinaryStream& stream) const { stream.writeArray(mItemData, &ItemData::write); }

Result<> ItemRegistryPacket::read(ReadOnlyBinaryStream& stream) { return stream.readArray(mItemData, &ItemData::read); }

std::string ItemRegistryPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mItemData)); }

} // namespace sculk::protocol::inline abi_v975
