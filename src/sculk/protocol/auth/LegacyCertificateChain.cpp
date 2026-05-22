// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/auth/LegacyCertificateChain.hpp"
#include "sculk/reflection/jsonc/reflection.hpp"
#include "ssl/ES384.hpp"

namespace sculk::protocol::inline abi_v975 {

bool Certificate::verify(std::string_view publicKeyPem) const {
    std::string signingInput = std::format("{}.{}", mRawHeader, mRawPayload);
    return es384::verifyES384Signature(signingInput, mSignature, publicKeyPem);
}

bool Certificate::sign(std::string_view privateKeyPem) {
    // TODO: update mRawHeader and mRawPayload based on the current state of the Certificate object before signing
    std::string signingInput = std::format("{}.{}", mRawHeader, mRawPayload);
    return es384::signES384Signature(signingInput, privateKeyPem, mSignature);
}

Result<Certificate> Certificate::fromString(std::string_view certificateStr) {
    // TODO: Implement actual parsing logic to populate the Certificate object based on the JWT structure of the
    // certificate string
}

std::string LegacyCertificateChain::toString() const {
    return ""; // TODO: Implement actual serialization logic
}

bool LegacyCertificateChain::verify(std::string_view publicKeyPem) const {
    (void)publicKeyPem;
    // TODO: Implement actual verification logic
    return true;
}

Result<LegacyCertificateChain> LegacyCertificateChain::fromString(std::string_view certificateChainJsonStr) {
    auto certJsonOpt = jsonc::json::parse(certificateChainJsonStr);
    if (!certJsonOpt) {
        return error_utils::makeError("Failed to parse certificate chain JSON");
    }

    const auto& certJson = *certJsonOpt;
    if (!certJson.contains("chain") || !certJson["chain"].is_array()) {
        return error_utils::makeError("Certificate JSON does not contain a valid 'chain' field");
    }

    std::size_t certCount = certJson["chain"].size();
    if (certCount == 1) {
        // TODO: offline mode, only login certificate is present
    } else if (certCount == 3) {
        // TODO: online mode, client and login certificates are present
    } else {
        return error_utils::makeError("Certificate JSON 'chain' field must contain either 1 or 3 certificates");
    }

    // TODO: Implement actual parsing logic to populate the LegacyCertificateChain object based on the JSON structure

    return LegacyCertificateChain{};
}

} // namespace sculk::protocol::inline abi_v975
