package com.flin.code.sender.service;

import com.flin.code.common.entity.AccountEntity;
import com.flin.code.common.entity.TransactionEntity;
import com.flin.code.sender.mapper.AccountMapper;
import com.flin.code.sender.mapper.TransactionMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.security.InvalidParameterException;
import java.util.List;

@Service
public class TransactionSenderService {

    @Autowired
    private AccountMapper accountMapper;

    @Autowired
    private TransactionMapper transactionMapper;

    @Transactional
    public void frozeTransactionAmount(Long userId, BigDecimal amount, String transactionId) {
        synchronized (AccountEntity.operationLocker) {
            AccountEntity account = accountMapper.getOne(userId);
            BigDecimal newAccountBalance = account.getAccountBalance().subtract(amount);
            if (newAccountBalance.compareTo(BigDecimal.ZERO) < 0) {
                throw new InvalidParameterException("User account balance insufficient.");
            }
            account.setAccountBalance(newAccountBalance);
            accountMapper.update(account);
        }
        transactionMapper.insert(new TransactionEntity(userId, amount, System.currentTimeMillis(),
                transactionId, "PENDING"));
    }

    public void finishTransaction(String transactionId) {
        synchronized (TransactionEntity.operationLocker) {
            List<TransactionEntity> entities = transactionMapper.getByTransactionId(transactionId);
            if (entities.size() == 1) {
                entities.get(0).setStatus("DONE");
                transactionMapper.update(entities.get(0));
            }
        }
    }

    public void rollbackTransaction(String transactionId) {
        List<TransactionEntity> entities = transactionMapper.getByTransactionId(transactionId);
        if (entities.size() == 1) {
            synchronized (AccountEntity.operationLocker) {
                AccountEntity account = accountMapper.getOne(entities.get(0).getUserId());
                account.setAccountBalance(account.getAccountBalance().add(entities.get(0).getAmount()));
                accountMapper.update(account);
            }
        }
    }

    public List<TransactionEntity> findOldTransaction() {
        Long time = System.currentTimeMillis() - 1000L * 3600L;
        return transactionMapper.getPendingTransactionByTime(time);
    }
}
