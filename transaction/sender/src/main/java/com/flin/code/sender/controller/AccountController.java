package com.flin.code.sender.controller;

import java.util.List;

import com.flin.code.common.entity.AccountEntity;
import com.flin.code.sender.mapper.AccountMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;


@RestController
public class AccountController {


    @Autowired
    private AccountMapper accountMapper;

    @GetMapping("/getUsers")
    public List<AccountEntity> getUsers() {
        List<AccountEntity> users = accountMapper.getAll();
        return users;
    }

    @GetMapping("/getUser")
    public AccountEntity getUser(Long id) {
        AccountEntity user = accountMapper.getOne(id);
        return user;
    }

    @PostMapping("/add")
    public void save(AccountEntity user) {
        accountMapper.insert(user);
    }

    @PutMapping(value = "update")
    public void update(AccountEntity user) {
        accountMapper.update(user);
    }

    @DeleteMapping(value = "/delete/{id}")
    public void delete(@PathVariable("id") Long id) {
        accountMapper.delete(id);
    }

}
