package com.flin.code.receiver.config;

import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.amqp.rabbit.annotation.RabbitListenerConfigurer;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.rabbit.listener.RabbitListenerEndpointRegistrar;
import org.springframework.amqp.support.converter.Jackson2JsonMessageConverter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.messaging.converter.MappingJackson2MessageConverter;
import org.springframework.messaging.handler.annotation.support.DefaultMessageHandlerMethodFactory;

@Configuration
public class RabbitConfig implements RabbitListenerConfigurer {

    public static final String EXCHANGE_NAME = "transactionExchange";
    public static final String TR_BEGIN_QUEUE = "transactionBeginQueue";
    public static final String TR_CONFIRM_QUEUE = "transactionConfirmQueue";
    public static final String ROUTING_BEGIN_KEY = "transaction.begin";
    public static final String ROUTING_CONFIRM_KEY = "transaction.confirm";

    @Bean
    public TopicExchange trExchange() {
        return new TopicExchange(EXCHANGE_NAME);
    }

    @Bean
    public Queue trBeginQueue() {
        return new Queue(TR_BEGIN_QUEUE);
    }

    @Bean
    public Queue trConfirmQueue() {
        return new Queue(TR_CONFIRM_QUEUE);
    }

    @Bean
    public Binding declareBindingActionQueue() {
        return BindingBuilder.bind(trBeginQueue()).to(trExchange()).with(ROUTING_BEGIN_KEY);
    }

    @Bean
    public Binding declareBindingConfirmQueue() {
        return BindingBuilder.bind(trConfirmQueue()).to(trExchange()).with(ROUTING_CONFIRM_KEY);
    }

    @Bean
    public Jackson2JsonMessageConverter producerJackson2MessageConverter() {
        return new Jackson2JsonMessageConverter();
    }

    @Bean
    public MappingJackson2MessageConverter consumerJackson2MessageConverter() {
        return new MappingJackson2MessageConverter();
    }

    @Bean
    public RabbitTemplate rabbitTemplate(final ConnectionFactory connectionFactory) {
        final RabbitTemplate rabbitTemplate = new RabbitTemplate(connectionFactory);
        rabbitTemplate.setMessageConverter(producerJackson2MessageConverter());
        return rabbitTemplate;
    }

    @Bean
    public DefaultMessageHandlerMethodFactory messageHandlerMethodFactory() {
        DefaultMessageHandlerMethodFactory factory = new DefaultMessageHandlerMethodFactory();
        factory.setMessageConverter(consumerJackson2MessageConverter());
        return factory;
    }

    @Override
    public void configureRabbitListeners(final RabbitListenerEndpointRegistrar registrar) {
        registrar.setMessageHandlerMethodFactory(messageHandlerMethodFactory());
    }

}
