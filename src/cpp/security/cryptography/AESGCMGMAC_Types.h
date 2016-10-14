// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file AESGCMGMAC_Types.h
 */

#ifndef _SECURITY_AUTHENTICATION_AESGCMGMAC_TYPES_H_
#define _SECURITY_AUTHENTICATION_AESGCMGMAC_TYPES_H_

#include <fastrtps/rtps/security/cryptography/CryptoTypes.h>
#include <fastrtps/rtps/attributes/PropertyPolicy.h>
#include <fastrtps/rtps/security/common/Handle.h>

//No encryption, no authentication tag
#define CRYPTO_TRANSFORMATION_KIND_NONE             {0, 0, 0, 0}

//No encryption, AES128-GMAC authentication
#define CRYPTO_TRANSFORMATION_KIND_AES128_GMAC      {0, 0, 0, 1}

//Authenticated encryption via AES128
#define CRYPTO_TRANSFORMATION_KIND_AES128_GCM       {0, 0, 0, 2}

//No encryption, AES256-GMAC authentication
#define CRYPTO_TRANSFORMATION_KIND_AES256_GMAC      {0, 0, 0, 3}

// Authenticated encryption via AES256-GMC
#define CRYPTO_TRANSFORMATION_KIND_AES256_GCM       {0, 0, 0, 4}

namespace eprosima {
namespace fastrtps {
namespace rtps {
namespace security {

struct KeyMaterial_AES_GCM_GMAC{
    CryptoTransformKind transformation_kind;
    std::array<uint8_t,32> master_salt;

    CryptoTransformKeyId sender_key_id;
    std::array<uint8_t, 32> master_sender_key;

    CryptoTransformKeyId receiver_specific_key_id;
    std::array<uint8_t, 32> master_receiver_specific_key;
};

struct SecureDataBody{
    std::vector<uint8_t> secure_data;
};

struct ReceiverSpecificMAC{
    CryptoTransformKeyId receiver_mac_key_id;
    std::array<uint8_t, 16> receiver_mac;
};

struct SecureDataTag{
    std::array<uint8_t, 16> common_mac;
    std::vector<ReceiverSpecificMAC> receiver_specific_macs;
};

class  ParticipantKeyMaterial
{
    public:
        ParticipantKeyMaterial():KeyMaterial(nullptr){}

        ~ParticipantKeyMaterial(){}

        static const char* const class_id_;

        KeyMaterial_AES_GCM_GMAC* KeyMaterial;
};

typedef HandleImpl<ParticipantKeyMaterial> AESGCMGMAC_ParticipantCryptoHandle;

} //namespaces security
} //namespace rtps
} //namespace fastrtps
} //namespace eprosima

#endif // _SECURITY_AUTHENTICATION_AESGCMGMAC_TYPES_H_
