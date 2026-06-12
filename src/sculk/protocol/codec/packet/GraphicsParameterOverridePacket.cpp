// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GraphicsParameterOverridePacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds GraphicsParameterOverridePacket::getId() const noexcept {
    return MinecraftPacketIds::GraphicsParameterOverride;
}
std::string_view GraphicsParameterOverridePacket::getName() const noexcept { return "GraphicsParameterOverridePacket"; }

void GraphicsParameterOverridePacket::write(BinaryStream& stream) const {
    stream.writeArray(mParameterKeyFrameValues, [](BinaryStream& stream, const ParameterKeyFrame& keyFrame) {
        stream.writeFloat(keyFrame.mTime);
        keyFrame.mValue.write(stream);
    });
    stream.writeFloat(mFloatValue);
    mVec3Value.write(stream);
    stream.writeString(mBiomeIdentifier);
    stream.writeEnum(mParameterType, &BinaryStream::writeByte);
    stream.writeBool(mResetParameter);
}

Result<> GraphicsParameterOverridePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(
        stream.readArray(mParameterKeyFrameValues, [](ReadOnlyBinaryStream& stream, ParameterKeyFrame& keyFrame) {
            _SCULK_READ(stream.readFloat(keyFrame.mTime));
            return keyFrame.mValue.read(stream);
        })
    );
    _SCULK_READ(stream.readFloat(mFloatValue));
    _SCULK_READ(mVec3Value.read(stream));
    _SCULK_READ(stream.readString(mBiomeIdentifier));
    _SCULK_READ(stream.readEnum(mParameterType, &ReadOnlyBinaryStream::readByte));
    return stream.readBool(mResetParameter);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string GraphicsParameterOverridePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mParameterKeyFrameValues),
        SCULK_FORMAT_FIELD(mBiomeIdentifier),
        SCULK_FORMAT_FIELD(mParameterType),
        SCULK_FORMAT_FIELD(mResetParameter),
        SCULK_FORMAT_FIELD(mFloatValue),
        SCULK_FORMAT_FIELD(mVec3Value)
    );
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
