package com.flin.code.strategy.base;


public abstract class PriceInRangeStrategy implements IStrategy {

    @Override
    public double getPrice(double distanceInKm) {
        double distanceInRange = distanceInKm <= getDownRange() ? 0 :
                distanceInKm <= getUpRange() ? distanceInKm - getDownRange() : getUpRange() - getDownRange();
        return distanceInRange * getPricePerKm();
    }

    protected abstract double getUpRange();
    protected abstract double getDownRange();
    protected abstract double getPricePerKm();

}
