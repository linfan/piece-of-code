package com.flin.code.receiver.mapper;

import com.flin.code.common.entity.AccountEntity;

import java.util.List;

public interface AccountMapper {

	List<AccountEntity> getAll();

	AccountEntity getOne(Long id);

	void insert(AccountEntity account);

	void update(AccountEntity account);

	void delete(Long id);

	void deleteAll();

}