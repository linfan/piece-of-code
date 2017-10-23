package com.flin.code.sender.service;

import com.flin.code.common.entity.enums.TransactionResult;
import com.flin.code.common.entity.message.TransactionConfirmMessage;
import com.flin.code.sender.config.RabbitConfig;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class TransactionMessageHandler {

    @Autowired
    private TransactionSenderService transactionSenderService;

    @RabbitListener(queues = RabbitConfig.TR_CONFIRM_QUEUE)
    public void receiveConfirmMessage(@Payload TransactionConfirmMessage message) {
        log.info("Received message as transaction confirm: {}", message.toString());
        if (message.getResult().equals(TransactionResult.DONE)) {
            transactionSenderService.finishTransaction(message.getTransactionId());
        } else {
            transactionSenderService.rollbackTransaction(message.getTransactionId());
        }
    }
}
