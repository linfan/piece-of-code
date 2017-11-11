package com.flin.code.service;


import com.flin.code.bean.TaxiType;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.sql.Time;
import java.util.Arrays;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class TaxiPriceServiceTest {

    TaxiPriceService taxiPriceService = new TaxiPriceService();

    @Parameters(name = "{index}: test({0})= at {1} of {2} drive {3}km")
    public static Iterable<Object[]> data() {
        return Arrays.asList(new Object[][] {
                // less than 3 km
                { 15.0, "14:00:00", TaxiType.INNER_RING, 2 }, { 18.0, "04:00:00", TaxiType.INNER_RING, 2 },
                { 15.0, "14:00:00", TaxiType.OUTER_RING, 2 }, { 18.0, "04:00:00", TaxiType.OUTER_RING, 2 },
                // at 3 km
                { 15.0, "14:00:00", TaxiType.INNER_RING, 3 }, { 18.0, "04:00:00", TaxiType.INNER_RING, 3 },
                { 15.0, "14:00:00", TaxiType.OUTER_RING, 3 }, { 18.0, "04:00:00", TaxiType.OUTER_RING, 3 },
                // between 3 and 10 km
                { 29.0, "14:00:00", TaxiType.INNER_RING, 7 }, { 30.0, "04:00:00", TaxiType.INNER_RING, 7 },
                { 29.0, "14:00:00", TaxiType.OUTER_RING, 7 }, { 30.0, "04:00:00", TaxiType.OUTER_RING, 7 },
                // at 10 km
                { 39.5, "14:00:00", TaxiType.INNER_RING, 10 }, { 39.0, "04:00:00", TaxiType.INNER_RING, 10 },
                { 39.5, "14:00:00", TaxiType.OUTER_RING, 10 }, { 39.0, "04:00:00", TaxiType.OUTER_RING, 10 },
                // more than 3 km
                { 57.0, "14:00:00", TaxiType.INNER_RING, 15 }, { 62.5, "04:00:00", TaxiType.INNER_RING, 15 },
                { 57.0, "14:00:00", TaxiType.OUTER_RING, 15 }, { 54.0, "04:00:00", TaxiType.OUTER_RING, 15 }
        });
    }

    private double price;
    private String time;
    private TaxiType taxiType;
    private double distance;

    public TaxiPriceServiceTest(double price, String time, TaxiType taxiType, double distance) {
        this.price = price;
        this.time = time;
        this.taxiType = taxiType;
        this.distance = distance;
    }

    @Test
    public void test_all_data() {
        assertEquals(price, taxiPriceService.calculatePrice(Time.valueOf(time), taxiType, distance), 0.01);
    }

}