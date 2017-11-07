package com.demo.strategy;

import com.demo.strategy.base.PriceInRangeStrategy;

public class After10KmAtNightInnerRingStrategy extends PriceInRangeStrategy {

    private final double PRICE_PER_KM = 4.7;
    private final double UP_RANGE = Integer.MAX_VALUE;
    private final double DOWN_RANGE = 10;

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
