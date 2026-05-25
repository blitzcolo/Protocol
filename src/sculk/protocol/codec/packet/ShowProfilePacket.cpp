// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ShowProfilePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ShowProfilePacket::getId() const noexcept { return MinecraftPacketIds::ShowProfile; }

std::string_view ShowProfilePacket::getName() const noexcept { return "ShowProfilePacket"; }

void ShowProfilePacket::write(BinaryStream& stream) const { stream.writeString(mXuid); }

Result<> ShowProfilePacket::read(ReadOnlyBinaryStream& stream) { return stream.readString(mXuid); }

std::string ShowProfilePacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mXuid)); }

} // namespace sculk::protocol::inline abi_v975
