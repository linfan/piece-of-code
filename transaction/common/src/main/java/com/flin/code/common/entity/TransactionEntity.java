package com.flin.code.common.entity;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.math.BigDecimal;
import java.sql.Timestamp;

@Data
@NoArgsConstructor
public class TransactionEntity implements Serializable {

    public static final Object operationLocker = new Object();
    private static final long serialVersionUID = 1L;
    private Long id;
    private Long userId;
    private BigDecimal amount;
    private Timestamp timestamp;
    private String transactionId;
    private String status;

    public TransactionEntity(Long userId, BigDecimal amount, Long time,
                             String transactionId, String status) {
        super();
        this.userId = userId;
        this.amount = amount;
        this.timestamp = new Timestamp(time);
        this.status = status;
    }

    @Override
    public String toString() {
        return "userId " + this.userId + ", amount " + this.amount.toString() +
                ", timestamp " + this.timestamp.toString() + ", status " + this.status;
    }
}
