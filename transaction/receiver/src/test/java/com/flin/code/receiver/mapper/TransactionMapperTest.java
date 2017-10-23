package com.flin.code.receiver.mapper;

import com.flin.code.common.entity.TransactionEntity;
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
public class TransactionMapperTest {

    @Autowired
    private TransactionMapper transactionMapper;

    @Test
    public void testInsert() throws Exception {
        transactionMapper.deleteAll();
        transactionMapper.insert(new TransactionEntity(1L, new BigDecimal(10000), System.currentTimeMillis(),
                "UUID", "PENDING"));
        transactionMapper.insert(new TransactionEntity(2L, new BigDecimal(20000), System.currentTimeMillis(),
                "UUID", "PENDING"));
        transactionMapper.insert(new TransactionEntity(3L, new BigDecimal(30000), System.currentTimeMillis(),
                "UUID", "PENDING"));

        Assert.assertThat(transactionMapper.getAll().size(), is(3));
    }

    @Test
    public void testQuery() throws Exception {
        transactionMapper.insert(new TransactionEntity(4L, new BigDecimal(40000), System.currentTimeMillis(),
                "UUID", "PENDING"));
        TransactionEntity user = transactionMapper.getAll().get(0);
        Assert.assertThat(transactionMapper.getOne(user.getId()).getAmount(), is(user.getAmount()));
    }


    @Test
    public void testUpdate() throws Exception {
        transactionMapper.insert(new TransactionEntity(5L, new BigDecimal(50000), System.currentTimeMillis(),
                "UUID", "PENDING"));
        TransactionEntity user = transactionMapper.getAll().get(0);
        System.out.println(user.toString());
        user.setAmount(new BigDecimal(60));
        transactionMapper.update(user);
        Assert.assertThat(new BigDecimal(60).compareTo(transactionMapper.getOne(user.getId()).getAmount()),
                is(0));
    }

}