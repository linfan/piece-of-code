package com.flin.code.sender.mocks;

import org.springframework.amqp.AmqpException;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;

public class FakeRabbitTemplate extends RabbitTemplate {

    public FakeRabbitTemplate(ConnectionFactory connectionFactory) {
        super(connectionFactory);
    }

    @Override
    public void convertAndSend(String exchange, String routingKey, Object object) throws AmqpException {
        this.convertAndSend(routingKey, object);
    }
}
