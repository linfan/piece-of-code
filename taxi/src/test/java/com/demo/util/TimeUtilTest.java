package com.demo.util;


import java.sql.Time;
import org.junit.Test;

import static org.junit.Assert.*;


public class TimeUtilTest {

    @Test
    public void should_23_00_be_at_night() {
        assertTrue(TimeUtil.isAtNight(Time.valueOf("23:00:00")));
    }

    @Test
    public void should_22_59_not_at_night() {
        assertFalse(TimeUtil.isAtNight(Time.valueOf("22:59:59")));
    }

    @Test
    public void should_05_59_be_at_night() {
        assertTrue(TimeUtil.isAtNight(Time.valueOf("05:59:59")));
    }

    @Test
    public void should_06_00_not_at_night() {
        assertFalse(TimeUtil.isAtNight(Time.valueOf("06:00:00")));
    }

}
