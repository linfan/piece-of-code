package com.flin.code.sender.service;

import com.flin.code.sender.config.RabbitConfig;
import com.flin.code.common.entity.message.TransactionBeginMessage;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class TransactionMessageSender {

    private final RabbitTemplate rabbitTemplate;

    @Autowired
    public TransactionMessageSender(final RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    public boolean beginTransaction(TransactionBeginMessage message) {
        log.info(String.format("begin transaction from %d to %d with id %s",
                message.getFrom(), message.getTo(), message.getTransactionId()));
        rabbitTemplate.convertAndSend(RabbitConfig.EXCHANGE_NAME, RabbitConfig.ROUTING_BEGIN_KEY, message);
        return true;
    }

}
