package com.flin.code.strategy;

import com.flin.code.strategy.base.IStrategy;
import org.junit.Test;

import java.sql.Time;
import java.util.List;

import static com.flin.code.bean.TaxiType.INNER_RING;
import static com.flin.code.bean.TaxiType.OUTER_RING;
import static org.junit.Assert.*;

public class StrategyChainTest {

    private StrategyChain strategyChain = new StrategyChain();

    @Test
    public void should_create_day_time_inner_ring_strategy_chain() {
        List<IStrategy> chain = strategyChain.createChain(Time.valueOf("14:00:00"), INNER_RING);
        assertEquals(3, chain.size());
        assertEquals(strategyChain.first3KmDayTimeStrategy, chain.get(0));
        assertEquals(strategyChain.from3To10KmDayTimeInnerRangeStrategy, chain.get(1));
        assertEquals(strategyChain.after10KmDayTimeInnerRingStrategy, chain.get(2));
    }

    @Test
    public void should_create_at_night_inner_ring_strategy_chain() {
        List<IStrategy> chain = strategyChain.createChain(Time.valueOf("04:00:00"), INNER_RING);
        assertEquals(3, chain.size());
        assertEquals(strategyChain.first3KmAtNightStrategy, chain.get(0));
        assertEquals(strategyChain.from3To10KmAtNightInnerRangeStrategy, chain.get(1));
        assertEquals(strategyChain.after10KmAtNightInnerRingStrategy, chain.get(2));
    }

    @Test
    public void should_create_day_time_outer_ring_strategy_chain() {
        List<IStrategy> chain = strategyChain.createChain(Time.valueOf("14:00:00"), OUTER_RING);
        assertEquals(2, chain.size());
        assertEquals(strategyChain.first3KmDayTimeStrategy, chain.get(0));
        assertEquals(strategyChain.after3KmDayTimeOuterRingStrategy, chain.get(1));
    }

    @Test
    public void should_create_at_night_outer_ring_strategy_chain() {
        List<IStrategy> chain = strategyChain.createChain(Time.valueOf("04:00:00"), OUTER_RING);
        assertEquals(2, chain.size());
        assertEquals(strategyChain.first3KmAtNightStrategy, chain.get(0));
        assertEquals(strategyChain.after3KmAtNightOuterRingStrategy, chain.get(1));
    }

}