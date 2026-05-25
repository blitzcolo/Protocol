// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/JigsawStructureDataPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds JigsawStructureDataPacket::getId() const noexcept { return MinecraftPacketIds::JigsawStructureData; }

std::string_view JigsawStructureDataPacket::getName() const noexcept { return "JigsawStructureDataPacket"; }

void JigsawStructureDataPacket::write(BinaryStream& stream) const { mData.write(stream); }

Result<> JigsawStructureDataPacket::read(ReadOnlyBinaryStream& stream) { return mData.read(stream); }

std::string JigsawStructureDataPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mData)); }

} // namespace sculk::protocol::inline abi_v975
