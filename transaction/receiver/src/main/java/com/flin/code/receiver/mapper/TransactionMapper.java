package com.flin.code.receiver.mapper;

import com.flin.code.common.entity.TransactionEntity;

import java.util.List;

public interface TransactionMapper {

	List<TransactionEntity> getAll();

	TransactionEntity getOne(Long id);

    List<TransactionEntity> getByTransactionId(String transactionId);

	void insert(TransactionEntity transaction);

	void update(TransactionEntity transaction);

	void delete(Long id);

	void deleteAll();

}