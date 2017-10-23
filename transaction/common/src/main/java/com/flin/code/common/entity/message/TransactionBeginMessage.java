package com.flin.code.common.entity.message;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.math.BigDecimal;

@Data
@AllArgsConstructor
@NoArgsConstructor
public final class TransactionBeginMessage implements Serializable{

    private long from;
    private long to;
    private BigDecimal amount;
    private String transactionId;

}
