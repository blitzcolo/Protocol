// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/Result.hpp"
#include <string>

namespace sculk::protocol::inline abi_v975 {

class ClientProperties {
public:
    [[nodiscard]] std::string toString() const;

public:
    [[nodiscard]] static Result<ClientProperties> fromString(std::string_view rawClientProperties);
};

} // namespace sculk::protocol::inline abi_v975