package com.flin.code.receiver.service;

import com.flin.code.receiver.config.RabbitConfig;
import com.flin.code.common.entity.message.TransactionConfirmMessage;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class TransactionMessageConfirmer {

    private final RabbitTemplate rabbitTemplate;

    @Autowired
    public TransactionMessageConfirmer(final RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    public boolean confirmTransaction(TransactionConfirmMessage message) {
        log.info("confirm transaction...");
        rabbitTemplate.convertAndSend(RabbitConfig.EXCHANGE_NAME, RabbitConfig.ROUTING_CONFIRM_KEY, message);
        return true;
    }
}
