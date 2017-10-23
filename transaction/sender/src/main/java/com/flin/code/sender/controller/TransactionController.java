package com.flin.code.sender.controller;

import com.flin.code.common.entity.message.TransactionBeginMessage;
import com.flin.code.common.utils.UserTokenValidator;
import com.flin.code.common.utils.UuidGenerator;
import com.flin.code.common.vo.ExceptionVo;
import com.flin.code.common.vo.TransactionVo;
import com.flin.code.sender.service.TransactionMessageSender;
import com.flin.code.sender.service.TransactionSenderService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.math.BigDecimal;
import java.security.InvalidParameterException;

@RestController
@Slf4j
public class TransactionController {

    @Autowired
    private TransactionMessageSender messageSender;

    @Autowired
    private TransactionSenderService transactionSenderService;

    @GetMapping("/doTransaction")
    public TransactionVo doTransaction(@RequestParam String from, @RequestParam String to,
                                @RequestParam String amount, @RequestHeader String userToken) {
        Long fromUserId = Long.parseLong(from);
        Long toUserId = Long.parseLong(to);
        BigDecimal decimalAmount = BigDecimal.valueOf(Long.parseLong(amount));
        if (UserTokenValidator.validate(fromUserId, userToken)) {
            String transactionId = UuidGenerator.gen();
            transactionSenderService.frozeTransactionAmount(fromUserId, decimalAmount,
                    transactionId);

            log.info(String.format("begin send $%s from %d user to %d user",
                    decimalAmount.toString(), fromUserId, toUserId));
            messageSender.beginTransaction(new TransactionBeginMessage(fromUserId,
                    toUserId, decimalAmount, transactionId));
        } else {
            log.warn(String.format("user %d token validation failed.", fromUserId));
            throw new InvalidParameterException("Invalid user token");
        }
        return new TransactionVo("Triggered");
    }

    @ExceptionHandler(value = {NumberFormatException.class, InvalidParameterException.class})
    public ExceptionVo exception(Exception e) {
        return new ExceptionVo(e.getMessage());
    }
}
