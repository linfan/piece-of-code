package com.flin.code.common.entity;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.math.BigDecimal;

@Data
@NoArgsConstructor
public class AccountEntity implements Serializable {

    public static final Object operationLocker = new Object();
    private static final long serialVersionUID = 1L;
    private Long id;
    private String userName;
    private BigDecimal accountBalance;

    public AccountEntity(String userName, BigDecimal accountBalance) {
        super();
        this.userName = userName;
        this.accountBalance = accountBalance;
    }

    @Override
    public String toString() {
        return "userName " + this.userName + ", accountBalance " + this.accountBalance.toString();
    }
}
