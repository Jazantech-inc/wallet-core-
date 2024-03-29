// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
#pragma once

#include "TWBase.h"
#include "TWData.h"
#include "TWString.h"

TW_EXTERN_C_BEGIN

/// Barz functions
TW_EXPORT_STRUCT
struct TWBarz;

/// Calculate a counterfactual address for the smart contract wallet
///
/// \param input The serialized data of ContractAddressInput.
/// \return The address.
TW_EXPORT_STATIC_METHOD
TWString *_Nonnull TWBarzGetCounterfactualAddress(TWData *_Nonnull input);

TW_EXTERN_C_END
