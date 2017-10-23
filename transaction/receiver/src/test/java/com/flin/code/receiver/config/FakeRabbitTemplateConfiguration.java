package com.flin.code.receiver.config;

import com.flin.code.receiver.mocks.FakeRabbitTemplate;
import com.flin.code.receiver.service.TransactionMessageHandler;
import com.rabbitmq.client.Channel;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.amqp.rabbit.connection.Connection;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

import static org.mockito.Matchers.anyBoolean;
import static org.mockito.Mockito.when;

@Configuration
public class FakeRabbitTemplateConfiguration {

    @Mock
    ConnectionFactory connectionFactory;

    @Mock
    Connection connection;

    @Mock
    Channel channel;

    public FakeRabbitTemplateConfiguration() {
        MockitoAnnotations.initMocks(this);
        when(connectionFactory.createConnection()).thenReturn(connection);
        when(connection.createChannel(anyBoolean())).thenReturn(channel);
    }

    @Bean
    @Primary
    @Autowired
    public RabbitTemplate rabbitTemplate(TransactionMessageHandler employeeEventHandler) {
        return new FakeRabbitTemplate(connectionFactory());
    }

    @Bean
    public ConnectionFactory connectionFactory() {
        return connectionFactory;
    }
}
