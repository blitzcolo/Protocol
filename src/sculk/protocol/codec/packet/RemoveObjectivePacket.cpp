// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RemoveObjectivePacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds RemoveObjectivePacket::getId() const noexcept { return MinecraftPacketIds::RemoveObjective; }

std::string_view RemoveObjectivePacket::getName() const noexcept { return "RemoveObjectivePacket"; }

void RemoveObjectivePacket::write(BinaryStream& stream) const { stream.writeString(mObjectiveName); }

Result<> RemoveObjectivePacket::read(ReadOnlyBinaryStream& stream) { return stream.readString(mObjectiveName); }

std::string RemoveObjectivePacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mObjectiveName)); }

} // namespace sculk::protocol::inline abi_v975
