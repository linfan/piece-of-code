package com.flin.code.receiver.service;

import com.flin.code.common.entity.AccountEntity;
import com.flin.code.common.entity.TransactionEntity;
import com.flin.code.common.entity.enums.TransactionResult;
import com.flin.code.common.entity.message.TransactionBeginMessage;
import com.flin.code.common.entity.message.TransactionConfirmMessage;
import com.flin.code.receiver.mapper.AccountMapper;
import com.flin.code.receiver.mapper.TransactionMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;

@Service
public class TransactionRecordService {

    @Autowired
    TransactionMapper transactionMapper;

    @Autowired
    AccountMapper accountMapper;

    @Autowired
    private TransactionMessageConfirmer messageSender;

    private boolean checkAndRecordTransacation(TransactionBeginMessage message) {
        synchronized (TransactionEntity.operationLocker) {
            if (transactionMapper.getByTransactionId(message.getTransactionId()).size() > 0) {
                return false;
            }
            transactionMapper.insert(new TransactionEntity(message.getFrom(), message.getAmount(),
                    System.currentTimeMillis(), message.getTransactionId(), "RECEIVED"));
        }
        return true;
    }

    @Transactional
    private void makeAccountBalanceChange(TransactionBeginMessage message) {
        synchronized (AccountEntity.operationLocker) {
            AccountEntity account = accountMapper.getOne(message.getTo());
            BigDecimal newAccountBalance = account.getAccountBalance().add(message.getAmount());
            account.setAccountBalance(newAccountBalance);
            accountMapper.update(account);
        }
    }

    @Transactional
    public boolean checkAndDoTransaction(TransactionBeginMessage message) {
        if (checkAndRecordTransacation(message)) {
            makeAccountBalanceChange(message);
            messageSender.confirmTransaction(new TransactionConfirmMessage(
                    message.getTransactionId(), TransactionResult.DONE));
            return true;
        } else {
            return false;
        }
    }

    public void sendRollbackMessage(TransactionBeginMessage message) {
        messageSender.confirmTransaction(new TransactionConfirmMessage(
                message.getTransactionId(), TransactionResult.FAILED));
    }
}
