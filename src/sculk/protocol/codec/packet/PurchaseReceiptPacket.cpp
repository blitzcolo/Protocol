// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PurchaseReceiptPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PurchaseReceiptPacket::getId() const noexcept { return MinecraftPacketIds::PurchaseReceipt; }

std::string_view PurchaseReceiptPacket::getName() const noexcept { return "PurchaseReceiptPacket"; }

void PurchaseReceiptPacket::write(BinaryStream& stream) const {
    stream.writeArray(mPurchaseProofs, &BinaryStream::writeString);
}

Result<> PurchaseReceiptPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mPurchaseProofs, &ReadOnlyBinaryStream::readString);
}

std::string PurchaseReceiptPacket::toString() const { return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mPurchaseProofs)); }

} // namespace sculk::protocol::inline abi_v975
