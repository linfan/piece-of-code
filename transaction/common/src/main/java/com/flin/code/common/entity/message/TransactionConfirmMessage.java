package com.flin.code.common.entity.message;

import com.flin.code.common.entity.enums.TransactionResult;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@Data
@AllArgsConstructor
@NoArgsConstructor
public final class TransactionConfirmMessage implements Serializable{

    private String transactionId;
    private TransactionResult result;

}
