package com.flin.code.strategy;

import com.flin.code.strategy.base.IStrategy;

public class First3KmDayTimeStrategy implements IStrategy {

    private final double FIXED_PRICE = 15;

    @Override
    public double getPrice(double distanceInKm) {
        return FIXED_PRICE;
    }
}
