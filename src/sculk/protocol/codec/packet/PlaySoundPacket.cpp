// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlaySoundPacket.hpp"
#include "../utility/Format.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PlaySoundPacket::getId() const noexcept { return MinecraftPacketIds::PlaySound; }

std::string_view PlaySoundPacket::getName() const noexcept { return "PlaySoundPacket"; }

void PlaySoundPacket::write(BinaryStream& stream) const {
    stream.writeString(mName);
    mPosition.write(stream);
    stream.writeFloat(mVolume);
    stream.writeFloat(mPitch);
    stream.writeOptional(mServerSoundHandle, &BinaryStream::writeUnsignedInt64);
}

Result<> PlaySoundPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mName));
    _SCULK_READ(mPosition.read(stream));
    _SCULK_READ(stream.readFloat(mVolume));
    _SCULK_READ(stream.readFloat(mPitch));
    return stream.readOptional(mServerSoundHandle, &ReadOnlyBinaryStream::readUnsignedInt64);
}

std::string PlaySoundPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mName),
        SCULK_FORMAT_FIELD(mPosition),
        SCULK_FORMAT_FIELD(mVolume),
        SCULK_FORMAT_FIELD(mPitch),
        SCULK_FORMAT_FIELD(mServerSoundHandle)
    );
}

} // namespace sculk::protocol::inline abi_v975
