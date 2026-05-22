// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/Base64Url.hpp"
#include <array>
#include <cstdint>
#include <memory>
#include <openssl/bio.h>
#include <openssl/core_names.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <span>
#include <string>
#include <vector>

namespace sculk::protocol::inline abi_v975::es384 {

constexpr std::size_t Es384ScalarSize = 48;
constexpr std::size_t Es384JoseSigLen = Es384ScalarSize * 2;

using BioPtr      = std::unique_ptr<BIO, decltype(&BIO_free)>;
using PkeyPtr     = std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)>;
using EcdsaSigPtr = std::unique_ptr<ECDSA_SIG, decltype(&ECDSA_SIG_free)>;
using BignumPtr   = std::unique_ptr<BIGNUM, decltype(&BN_free)>;
using MdCtxPtr    = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>;

[[nodiscard]] inline bool isEs384Key(const EVP_PKEY* key) {
    if (!key || EVP_PKEY_base_id(key) != EVP_PKEY_EC || EVP_PKEY_get_bits(key) != 384) {
        return false;
    }

    std::array<char, 32> curveName{};
    std::size_t          curveNameLen = 0;
    if (EVP_PKEY_get_utf8_string_param(
            key,
            OSSL_PKEY_PARAM_GROUP_NAME,
            curveName.data(),
            curveName.size(),
            &curveNameLen
        ) != 1
        || curveNameLen == 0) {
        return false;
    }

    std::string_view curve(curveName.data(), curveNameLen);
    return curve == "secp384r1" || curve == "P-384";
}

[[nodiscard]] inline MdCtxPtr makeMdCtx() { return MdCtxPtr(EVP_MD_CTX_new(), EVP_MD_CTX_free); }

[[nodiscard]] inline PkeyPtr loadPublicKey(std::string_view pem) {
    BioPtr bio(BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())), BIO_free);
    if (!bio) {
        return PkeyPtr(nullptr, EVP_PKEY_free);
    }

    PkeyPtr key(PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr), EVP_PKEY_free);
    if (!isEs384Key(key.get())) {
        return PkeyPtr(nullptr, EVP_PKEY_free);
    }
    return key;
}

[[nodiscard]] inline PkeyPtr loadPrivateKey(std::string_view pem) {
    BioPtr bio(BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())), BIO_free);
    if (!bio) {
        return PkeyPtr(nullptr, EVP_PKEY_free);
    }

    PkeyPtr key(PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, nullptr), EVP_PKEY_free);
    if (!isEs384Key(key.get())) {
        return PkeyPtr(nullptr, EVP_PKEY_free);
    }
    return key;
}

[[nodiscard]] inline bool joseEs384ToDer(std::string_view joseSig, std::vector<std::uint8_t>& derOut) {
    if (joseSig.size() != Es384JoseSigLen) {
        return false;
    }

    EcdsaSigPtr ecdsaSig(ECDSA_SIG_new(), ECDSA_SIG_free);
    if (!ecdsaSig) {
        return false;
    }

    BignumPtr r(
        BN_bin2bn(reinterpret_cast<const std::uint8_t*>(joseSig.data()), static_cast<int>(Es384ScalarSize), nullptr),
        BN_free
    );
    BignumPtr s(
        BN_bin2bn(
            reinterpret_cast<const std::uint8_t*>(joseSig.data() + Es384ScalarSize),
            static_cast<int>(Es384ScalarSize),
            nullptr
        ),
        BN_free
    );

    if (!r || !s) {
        return false;
    }

    if (ECDSA_SIG_set0(ecdsaSig.get(), r.release(), s.release()) != 1) {
        return false;
    }

    int derLen = i2d_ECDSA_SIG(ecdsaSig.get(), nullptr);
    if (derLen <= 0) {
        return false;
    }

    derOut.resize(static_cast<std::size_t>(derLen));
    std::uint8_t* out = derOut.data();
    if (i2d_ECDSA_SIG(ecdsaSig.get(), &out) != derLen) {
        derOut.clear();
        return false;
    }

    return true;
}

[[nodiscard]] inline bool
derToJoseEs384(const std::uint8_t* der, std::size_t derLen, std::array<std::uint8_t, Es384JoseSigLen>& joseOut) {
    const std::uint8_t* p = der;
    EcdsaSigPtr         ecdsaSig(d2i_ECDSA_SIG(nullptr, &p, static_cast<long>(derLen)), ECDSA_SIG_free);
    if (!ecdsaSig || p != der + derLen) {
        return false;
    }

    const BIGNUM* r = nullptr;
    const BIGNUM* s = nullptr;
    ECDSA_SIG_get0(ecdsaSig.get(), &r, &s);
    if (!r || !s) {
        return false;
    }

    if (BN_num_bytes(r) > static_cast<int>(Es384ScalarSize) || BN_num_bytes(s) > static_cast<int>(Es384ScalarSize)) {
        return false;
    }

    joseOut.fill(0);
    if (BN_bn2binpad(r, joseOut.data(), static_cast<int>(Es384ScalarSize)) != static_cast<int>(Es384ScalarSize)) {
        return false;
    }
    if (BN_bn2binpad(s, joseOut.data() + Es384ScalarSize, static_cast<int>(Es384ScalarSize))
        != static_cast<int>(Es384ScalarSize)) {
        return false;
    }

    return true;
}

[[nodiscard]] inline bool
verifyES384Signature(std::string_view signingInput, std::string_view signature, std::string_view publicKeyPem) {
    if (signingInput.empty()) {
        return false;
    }

    auto joseSig = base64url::decodeChecked(signature, Es384JoseSigLen);
    if (!joseSig) {
        return false;
    }

    std::vector<std::uint8_t> derSig{};
    if (!joseEs384ToDer(*joseSig, derSig)) {
        return false;
    }

    auto publicKey = loadPublicKey(publicKeyPem);
    if (!publicKey) {
        return false;
    }

    auto mdCtx = makeMdCtx();
    if (!mdCtx) {
        return false;
    }

    if (EVP_DigestVerifyInit(mdCtx.get(), nullptr, EVP_sha384(), nullptr, publicKey.get()) != 1) {
        return false;
    }

    if (EVP_DigestVerifyUpdate(mdCtx.get(), signingInput.data(), signingInput.size()) != 1) {
        return false;
    }

    return EVP_DigestVerifyFinal(mdCtx.get(), derSig.data(), derSig.size()) == 1;
}

[[nodiscard]] inline bool
signES384Signature(std::string_view signingInput, std::string_view privateKeyPem, std::string& outSignature) {
    outSignature.clear();

    if (signingInput.empty()) {
        return false;
    }

    auto privateKey = loadPrivateKey(privateKeyPem);
    if (!privateKey) {
        return false;
    }

    auto mdCtx = makeMdCtx();
    if (!mdCtx) {
        return false;
    }

    if (EVP_DigestSignInit(mdCtx.get(), nullptr, EVP_sha384(), nullptr, privateKey.get()) != 1) {
        return false;
    }

    if (EVP_DigestSignUpdate(mdCtx.get(), signingInput.data(), signingInput.size()) != 1) {
        return false;
    }

    std::size_t derLen = 0;
    if (EVP_DigestSignFinal(mdCtx.get(), nullptr, &derLen) != 1 || derLen == 0) {
        return false;
    }

    std::vector<std::uint8_t> derSig(derLen);
    if (EVP_DigestSignFinal(mdCtx.get(), derSig.data(), &derLen) != 1) {
        return false;
    }
    derSig.resize(derLen);

    std::array<std::uint8_t, Es384JoseSigLen> joseSig{};
    if (!derToJoseEs384(derSig.data(), derSig.size(), joseSig)) {
        return false;
    }

    outSignature = base64url::encode(std::span<const std::uint8_t>(joseSig));
    return true;
}

} // namespace sculk::protocol::inline abi_v975::es384