package com.flin.code.strategy;

import com.flin.code.bean.TaxiType;
import com.flin.code.exception.ImpossibleTimeAndTypeException;
import com.flin.code.strategy.base.IStrategy;
import com.flin.code.util.TimeUtil;
import com.google.common.collect.ImmutableList;

import java.sql.Time;
import java.util.List;

public class StrategyChain {

    final After3KmAtNightOuterRingStrategy after3KmAtNightOuterRingStrategy = new After3KmAtNightOuterRingStrategy();
    final After3KmDayTimeOuterRingStrategy after3KmDayTimeOuterRingStrategy = new After3KmDayTimeOuterRingStrategy();
    final After10KmAtNightInnerRingStrategy after10KmAtNightInnerRingStrategy = new After10KmAtNightInnerRingStrategy();
    final After10KmDayTimeInnerRingStrategy after10KmDayTimeInnerRingStrategy = new After10KmDayTimeInnerRingStrategy();
    final First3KmAtNightStrategy first3KmAtNightStrategy = new First3KmAtNightStrategy();
    final First3KmDayTimeStrategy first3KmDayTimeStrategy = new First3KmDayTimeStrategy();
    final From3To10KmAtNightInnerRangeStrategy from3To10KmAtNightInnerRangeStrategy = new From3To10KmAtNightInnerRangeStrategy();
    final From3To10KmDayTimeInnerRangeStrategy from3To10KmDayTimeInnerRangeStrategy = new From3To10KmDayTimeInnerRangeStrategy();

    public List<IStrategy> createChain(Time startTime, TaxiType taxiType) {
        if (TimeUtil.isAtNight(startTime)) {
            switch (taxiType) {
                case INNER_RING:
                    return ImmutableList.of(first3KmAtNightStrategy,
                            from3To10KmAtNightInnerRangeStrategy,
                            after10KmAtNightInnerRingStrategy);
                case OUTER_RING:
                    return ImmutableList.of(first3KmAtNightStrategy,
                            after3KmAtNightOuterRingStrategy);
            }
        } else {
            switch (taxiType) {
                case INNER_RING:
                    return ImmutableList.of(first3KmDayTimeStrategy,
                            from3To10KmDayTimeInnerRangeStrategy,
                            after10KmDayTimeInnerRingStrategy);
                case OUTER_RING:
                    return ImmutableList.of(first3KmDayTimeStrategy,
                            after3KmDayTimeOuterRingStrategy);
            }
        }
        // impossible to reach here
        throw new ImpossibleTimeAndTypeException("Cannot create a proper strategy chain");
    }

}
