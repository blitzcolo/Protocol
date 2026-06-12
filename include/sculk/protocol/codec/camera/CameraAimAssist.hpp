// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/math/Vec2.hpp"
#include "sculk/protocol/utility/BinaryStream.hpp"
#include "sculk/protocol/utility/Enum.hpp"
#include "sculk/protocol/utility/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

struct CameraAimAssistCategoryPriorities {
    struct PriorityEntry {
        std::string  mName{};
        std::int32_t mPriority{};
    };

    std::vector<PriorityEntry>  mEntities{};
    std::vector<PriorityEntry>  mBlocks{};
    std::optional<std::int32_t> mEntityDefault{};
    std::optional<std::int32_t> mBlockDefault{};
    std::vector<PriorityEntry>  mBlockTags{};
    std::vector<PriorityEntry>  mEntityTypeFamilies{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistCategoryDefinition {
    std::string                       mName{};
    CameraAimAssistCategoryPriorities mPriorities{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistCategoriesDefinition {
    std::string                                    mIdentifier{};
    std::vector<CameraAimAssistCategoryDefinition> mCategory{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistPresetDefinition {
    struct ItemSetting {
        std::string mItemName{};
        std::string mCategory{};
    };

    std::string                mIdentifier{};
    std::string                mCategories{};
    std::vector<std::string>   mExclusionList{};
    std::vector<std::string>   mLiquidTargetingList{};
    std::vector<ItemSetting>   mItemSettings{};
    std::optional<std::string> mDefaultItemSettings{};
    std::optional<std::string> mHandSettings{};
    std::vector<std::string>   mBlockExclusionList{};
    std::vector<std::string>   mBlockTagExclusionList{};
    std::vector<std::string>   mEntityExclusionList{};
    std::vector<std::string>   mEntityTypeFamilyExclusionList{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

class CameraPresetAimAssistDefinition {
public:
    enum class TargetMode : std::uint8_t {
        Angle    = 0,
        Distance = 1,
    };

public:
    std::optional<std::string> mPresetId{};
    std::optional<TargetMode>  mTargetMode{};
    std::optional<Vec2>        mViewAngle{};
    std::optional<float>       mDistance{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE

SCULK_PROTOCOL_ENUM_RANGE(CameraPresetAimAssistDefinition::TargetMode, 0, 1);
