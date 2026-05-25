// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PrimitiveShapesPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PrimitiveShapesPacket::getId() const noexcept { return MinecraftPacketIds::PrimitiveShapes; }

std::string_view PrimitiveShapesPacket::getName() const noexcept { return "PrimitiveShapesPacket"; }

void PrimitiveShapesPacket::write(BinaryStream& stream) const { stream.writeArray(mShapes, &PrimitiveShapes::write); }

Result<> PrimitiveShapesPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mShapes, &PrimitiveShapes::read);
}

std::string PrimitiveShapesPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mShapes)); }

} // namespace sculk::protocol::inline abi_v975
