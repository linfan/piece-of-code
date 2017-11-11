package com.flin.code.strategy;

import com.flin.code.strategy.base.PriceInRangeStrategy;

public class From3To10KmAtNightInnerRangeStrategy extends PriceInRangeStrategy {

    private final double PRICE_PER_KM = 3.0;
    private final double UP_RANGE = 10;
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
