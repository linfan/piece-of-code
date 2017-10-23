package com.flin.code.receiver.service;

import com.flin.code.common.entity.message.TransactionBeginMessage;
import com.flin.code.receiver.config.RabbitConfig;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class TransactionMessageHandler {

    @Autowired
    private TransactionRecordService transactionRecordService;

    @RabbitListener(queues = RabbitConfig.TR_BEGIN_QUEUE)
    public void receiveActionMessage(@Payload TransactionBeginMessage message) {
        log.info("Received message as transaction action: {}", message.toString());

        try {
            if (!transactionRecordService.checkAndDoTransaction(message)) {
                log.warn(String.format("Duplicated transaction message with %s", message.getTransactionId()));
            }
        } catch (Exception e) {
            transactionRecordService.sendRollbackMessage(message);
        }

    }

}
