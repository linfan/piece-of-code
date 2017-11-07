package com.demo.service;

import com.demo.bean.TaxiType;
import com.demo.strategy.StrategyChain;
import com.demo.strategy.base.IStrategy;

import java.sql.Time;
import java.util.List;

public class TaxiPriceService {

    StrategyChain strategyChain = new StrategyChain();

    public double calculatePrice(Time startTime, TaxiType taxiType, double distanceInKm) {
        List<IStrategy> chain = strategyChain.createChain(startTime, taxiType);
        return chain.stream()
                .map(strategy -> strategy.getPrice(distanceInKm))
                .reduce((a, b) -> a + b).get();
    }

}
