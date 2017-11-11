package com.flin.code.service;

import com.flin.code.bean.TaxiType;
import com.flin.code.strategy.StrategyChain;
import com.flin.code.strategy.base.IStrategy;

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
