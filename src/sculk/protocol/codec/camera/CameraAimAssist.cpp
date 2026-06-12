// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/camera/CameraAimAssist.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void CameraAimAssistCategoryPriorities::write(BinaryStream& stream) const {
    stream.writeArray(mEntities, [](BinaryStream& stream, const PriorityEntry& entry) {
        stream.writeString(entry.mName);
        stream.writeSignedInt(entry.mPriority);
    });
    stream.writeArray(mBlocks, [](BinaryStream& stream, const PriorityEntry& entry) {
        stream.writeString(entry.mName);
        stream.writeSignedInt(entry.mPriority);
    });
    stream.writeArray(mBlockTags, [](BinaryStream& stream, const PriorityEntry& entry) {
        stream.writeString(entry.mName);
        stream.writeSignedInt(entry.mPriority);
    });
    stream.writeArray(mEntityTypeFamilies, [](BinaryStream& stream, const PriorityEntry& entry) {
        stream.writeString(entry.mName);
        stream.writeSignedInt(entry.mPriority);
    });
    stream.writeOptional(mEntityDefault, &BinaryStream::writeSignedInt);
    stream.writeOptional(mBlockDefault, &BinaryStream::writeSignedInt);
}

Result<> CameraAimAssistCategoryPriorities::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mEntities, [](ReadOnlyBinaryStream& stream, PriorityEntry& entry) {
        _SCULK_READ(stream.readString(entry.mName));
        return stream.readSignedInt(entry.mPriority);
    }));
    _SCULK_READ(stream.readArray(mBlocks, [](ReadOnlyBinaryStream& stream, PriorityEntry& entry) {
        _SCULK_READ(stream.readString(entry.mName));
        return stream.readSignedInt(entry.mPriority);
    }));
    _SCULK_READ(stream.readArray(mBlockTags, [](ReadOnlyBinaryStream& stream, PriorityEntry& entry) {
        _SCULK_READ(stream.readString(entry.mName));
        return stream.readSignedInt(entry.mPriority);
    }));
    _SCULK_READ(stream.readArray(mEntityTypeFamilies, [](ReadOnlyBinaryStream& stream, PriorityEntry& entry) {
        _SCULK_READ(stream.readString(entry.mName));
        return stream.readSignedInt(entry.mPriority);
    }));
    _SCULK_READ(stream.readOptional(mEntityDefault, &ReadOnlyBinaryStream::readSignedInt));
    return stream.readOptional(mBlockDefault, &ReadOnlyBinaryStream::readSignedInt);
}

void CameraAimAssistCategoryDefinition::write(BinaryStream& stream) const {
    stream.writeString(mName);
    mPriorities.write(stream);
}

Result<> CameraAimAssistCategoryDefinition::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mName));
    return mPriorities.read(stream);
}

void CameraAimAssistCategoriesDefinition::write(BinaryStream& stream) const {
    stream.writeString(mIdentifier);
    stream.writeArray(mCategory, &CameraAimAssistCategoryDefinition::write);
}

Result<> CameraAimAssistCategoriesDefinition::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mIdentifier));
    return stream.readArray(mCategory, &CameraAimAssistCategoryDefinition::read);
}

void CameraAimAssistPresetDefinition::write(BinaryStream& stream) const {
    stream.writeString(mIdentifier);
    stream.writeArray(mBlockExclusionList, &BinaryStream::writeString);
    stream.writeArray(mEntityExclusionList, &BinaryStream::writeString);
    stream.writeArray(mBlockTagExclusionList, &BinaryStream::writeString);
    stream.writeArray(mEntityTypeFamilyExclusionList, &BinaryStream::writeString);
    stream.writeArray(mLiquidTargetingList, &BinaryStream::writeString);
    stream.writeArray(mItemSettings, [](BinaryStream& stream, const ItemSetting& setting) {
        stream.writeString(setting.mItemName);
        stream.writeString(setting.mCategory);
    });
    stream.writeOptional(mDefaultItemSettings, &BinaryStream::writeString);
    stream.writeOptional(mHandSettings, &BinaryStream::writeString);
}

Result<> CameraAimAssistPresetDefinition::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mIdentifier));
    _SCULK_READ(stream.readArray(mBlockExclusionList, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readArray(mEntityExclusionList, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readArray(mBlockTagExclusionList, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readArray(mEntityTypeFamilyExclusionList, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readArray(mLiquidTargetingList, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readArray(mItemSettings, [](ReadOnlyBinaryStream& stream, ItemSetting& setting) {
        _SCULK_READ(stream.readString(setting.mItemName));
        return stream.readString(setting.mCategory);
    }));
    _SCULK_READ(stream.readOptional(mDefaultItemSettings, &ReadOnlyBinaryStream::readString));
    return stream.readOptional(mHandSettings, &ReadOnlyBinaryStream::readString);
}

void CameraPresetAimAssistDefinition::write(BinaryStream& stream) const {
    stream.writeOptional(mPresetId, &BinaryStream::writeString);
    stream.writeOptional(mTargetMode, [](BinaryStream& stream, TargetMode value) {
        stream.writeEnum(value, &BinaryStream::writeByte);
    });
    stream.writeOptional(mViewAngle, &Vec2::write);
    stream.writeOptional(mDistance, &BinaryStream::writeFloat);
}

Result<> CameraPresetAimAssistDefinition::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readOptional(mPresetId, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readOptional(mTargetMode, [](ReadOnlyBinaryStream& stream, TargetMode& value) {
        return stream.readEnum(value, &ReadOnlyBinaryStream::readByte);
    }));
    _SCULK_READ(stream.readOptional(mViewAngle, &Vec2::read));
    return stream.readOptional(mDistance, &ReadOnlyBinaryStream::readFloat);
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
