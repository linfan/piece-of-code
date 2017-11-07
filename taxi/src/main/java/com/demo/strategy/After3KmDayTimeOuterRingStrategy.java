package com.demo.strategy;

import com.demo.strategy.base.PriceInRangeStrategy;

public class After3KmDayTimeOuterRingStrategy  extends PriceInRangeStrategy {

    private final double PRICE_PER_KM = 3.5;
    private final double UP_RANGE = Integer.MAX_VALUE;
    private final double DOWN_RANGE = 3;

    @Override
    protected double getUpRange() {
        return UP_RANGE;
    }

    @Override
    protected double getDownRange() {
        return DOWN_RANGE;
    }

    @Override
    protected double getPricePerKm() {
        return PRICE_PER_KM;
    }
}
