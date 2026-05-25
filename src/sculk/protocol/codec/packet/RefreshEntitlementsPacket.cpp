// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RefreshEntitlementsPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds RefreshEntitlementsPacket::getId() const noexcept { return MinecraftPacketIds::RefreshEntitlements; }

std::string_view RefreshEntitlementsPacket::getName() const noexcept { return "RefreshEntitlementsPacket"; }

void RefreshEntitlementsPacket::write(BinaryStream&) const {}

Result<> RefreshEntitlementsPacket::read(ReadOnlyBinaryStream&) { return {}; }

std::string RefreshEntitlementsPacket::toString() const { return SCULK_FORMAT_PACKET(); }

} // namespace sculk::protocol::inline abi_v975
