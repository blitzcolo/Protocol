// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#if __has_include(<magic_enum/magic_enum.hpp>)
#include <magic_enum/magic_enum.hpp>
#define SCULK_PROTOCOL_ENUM_RANGE(ENUM_CLASS, MIN, MAX)                                                                \
    template <>                                                                                                        \
    struct magic_enum::customize::enum_range<sculk::protocol::ENUM_CLASS> {                                            \
        static constexpr int min = MIN;                                                                                \
        static constexpr int max = MAX;                                                                                \
    }
#define SCULK_PROTOCOL_ENUM_IS_FLAGS(ENUM_CLASS)                                                                       \
    template <>                                                                                                        \
    struct magic_enum::customize::enum_range<sculk::protocol::ENUM_CLASS> {                                            \
        static constexpr bool is_flags = true;                                                                         \
    }
#else
#define SCULK_PROTOCOL_ENUM_RANGE(ENUM_CLASS, MIN, MAX)
#define SCULK_PROTOCOL_ENUM_IS_FLAGS(ENUM_CLASS)
#endif