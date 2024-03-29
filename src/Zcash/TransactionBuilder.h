// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"
#include "../Bitcoin/TransactionBuilder.h"
#include "../Bitcoin/TransactionPlan.h"
#include "../proto/Bitcoin.pb.h"
#include  "../HexCoding.h"
#include "../Result.h"
#include <TrustWalletCore/TWCoinType.h>

#include <algorithm>

namespace TW::Zcash {

struct TransactionBuilder {
    /// Plans a transaction by selecting UTXOs and calculating fees.
    static Bitcoin::TransactionPlan plan(const Bitcoin::SigningInput& input) {
        return Bitcoin::TransactionBuilder::plan(input);
    }

    /// Builds a transaction by selecting UTXOs and calculating fees.
    template <typename Transaction>
    static Result<Transaction, Common::Proto::SigningError> build(const Bitcoin::TransactionPlan& plan, const std::string& toAddress,
                             const std::string& changeAddress, enum TWCoinType coin, uint32_t lockTime) {
        coin = TWCoinTypeZcash;
        auto tx_result =
            Bitcoin::TransactionBuilder::build<Transaction>(plan, toAddress, changeAddress, coin, lockTime);
        if (!tx_result) { return Result<Transaction, Common::Proto::SigningError>::failure(tx_result.error()); }
        Transaction tx = tx_result.payload();
        // if not set, always use latest consensus branch id
        if (plan.branchId.empty()) {
            std::copy(BlossomBranchID.begin(), BlossomBranchID.end(), tx.branchId.begin());
        } else {
            std::copy(plan.branchId.begin(), plan.branchId.end(), tx.branchId.begin());
        }
        return Result<Transaction, Common::Proto::SigningError>(tx);
    }
};

} // namespace TW::Zcash
