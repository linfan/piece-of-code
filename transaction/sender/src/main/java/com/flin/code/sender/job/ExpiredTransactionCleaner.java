package com.flin.code.sender.job;

import com.flin.code.sender.service.TransactionSenderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

@Service
public class ExpiredTransactionCleaner {

    @Autowired
    private TransactionSenderService transactionSenderService;

    @Scheduled(fixedDelay = 60000L)
    public void handleExpiredTransaction() {
        transactionSenderService.findOldTransaction().forEach((transaction -> {
            transactionSenderService.rollbackTransaction(transaction.getTransactionId());
        }));
    }

}
