package com.flin.code.sender.mapper;

import com.flin.code.common.entity.AccountEntity;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.math.BigDecimal;

import static org.hamcrest.CoreMatchers.is;

@RunWith(SpringRunner.class)
@SpringBootTest
public class AccountMapperTest {

    @Autowired
    private AccountMapper accountMapper;

    @Test
    public void testInsert() throws Exception {
        accountMapper.deleteAll();
        accountMapper.insert(new AccountEntity("a123456", new BigDecimal(10000)));
        accountMapper.insert(new AccountEntity("b123457", new BigDecimal(20000)));
        accountMapper.insert(new AccountEntity("b123458", new BigDecimal(30000)));

        Assert.assertThat(accountMapper.getAll().size(), is(3));
    }

    @Test
    public void testQuery() throws Exception {
        accountMapper.insert(new AccountEntity("b123459", new BigDecimal(40000)));
        AccountEntity user = accountMapper.getAll().get(0);
        Assert.assertThat(accountMapper.getOne(user.getId()).getAccountBalance(), is(user.getAccountBalance()));
    }


    @Test
    public void testUpdate() throws Exception {
        accountMapper.insert(new AccountEntity("b123460", new BigDecimal(50000)));
        AccountEntity user = accountMapper.getAll().get(0);
        System.out.println(user.toString());
        user.setAccountBalance(new BigDecimal(6));
        accountMapper.update(user);
        Assert.assertThat(new BigDecimal(6).compareTo(accountMapper.getOne(user.getId()).getAccountBalance()),
                is(0));
    }

}