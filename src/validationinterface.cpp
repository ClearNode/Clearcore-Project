// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "validationinterface.h"

static CMainSignals g_signals;

CMainSignals& GetMainSignals()
{
    return g_signals;
}

void RegisterValidationInterface(CValidationInterface* pwalletIn) {

// XX42 g_signals.EraseTransaction.connect(std::bind(&CValidationInterface::EraseFromWallet, pwalletIn, boost::placeholders::_1));
    g_signals.UpdatedBlockTip.connect(std::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, boost::placeholders::_1));
    g_signals.SyncTransaction.connect(std::bind(&CValidationInterface::SyncTransaction, pwalletIn, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3));
    g_signals.NotifyTransactionLock.connect(std::bind(&CValidationInterface::NotifyTransactionLock, pwalletIn, boost::placeholders::_1));
    g_signals.UpdatedTransaction.connect(std::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, boost::placeholders::_1));
    g_signals.SetBestChain.connect(std::bind(&CValidationInterface::SetBestChain, pwalletIn, boost::placeholders::_1));
    g_signals.Broadcast.connect(std::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, boost::placeholders::_1));
    g_signals.BlockChecked.connect(std::bind(&CValidationInterface::BlockChecked, pwalletIn, boost::placeholders::_1, boost::placeholders::_2));
// XX42    g_signals.ScriptForMining.connect(std::bind(&CValidationInterface::GetScriptForMining, pwalletIn, boost::placeholders::_1));
    g_signals.BlockFound.connect(std::bind(&CValidationInterface::ResetRequestCount, pwalletIn, boost::placeholders::_1));
}

void UnregisterValidationInterface(CValidationInterface* pwalletIn) {
    g_signals.BlockFound.disconnect(std::bind(&CValidationInterface::ResetRequestCount, pwalletIn, boost::placeholders::_1));
// XX42    g_signals.ScriptForMining.disconnect(std::bind(&CValidationInterface::GetScriptForMining, pwalletIn, boost::placeholders::_1));
    g_signals.BlockChecked.disconnect(std::bind(&CValidationInterface::BlockChecked, pwalletIn, boost::placeholders::_1, boost::placeholders::_2));
    g_signals.Broadcast.disconnect(std::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, boost::placeholders::_1));
    g_signals.SetBestChain.disconnect(std::bind(&CValidationInterface::SetBestChain, pwalletIn, boost::placeholders::_1));
    g_signals.UpdatedTransaction.disconnect(std::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, boost::placeholders::_1));
    g_signals.NotifyTransactionLock.disconnect(std::bind(&CValidationInterface::NotifyTransactionLock, pwalletIn, boost::placeholders::_1));
    g_signals.SyncTransaction.disconnect(std::bind(&CValidationInterface::SyncTransaction, pwalletIn, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3));
    g_signals.UpdatedBlockTip.disconnect(std::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, boost::placeholders::_1));
// XX42    g_signals.EraseTransaction.disconnect(std::bind(&CValidationInterface::EraseFromWallet, pwalletIn, boost::placeholders::_1));

}

void UnregisterAllValidationInterfaces() {
    g_signals.BlockFound.disconnect_all_slots();
// XX42    g_signals.ScriptForMining.disconnect_all_slots();
    g_signals.BlockChecked.disconnect_all_slots();
    g_signals.Broadcast.disconnect_all_slots();
    g_signals.SetBestChain.disconnect_all_slots();
    g_signals.UpdatedTransaction.disconnect_all_slots();
    g_signals.NotifyTransactionLock.disconnect_all_slots();
    g_signals.SyncTransaction.disconnect_all_slots();
    g_signals.UpdatedBlockTip.disconnect_all_slots();
// XX42    g_signals.EraseTransaction.disconnect_all_slots();
}
