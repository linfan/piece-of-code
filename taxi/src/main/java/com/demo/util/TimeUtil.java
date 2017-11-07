package com.demo.util;

import java.sql.Time;

public class TimeUtil {

    private static final Time EARLY_EDGE = Time.valueOf("06:00:00");
    private static final Time LATE_EDGE = Time.valueOf("23:00:00");

    public static boolean isAtNight(Time time) {
        return time.after(LATE_EDGE) || time.equals(LATE_EDGE) || time.before(EARLY_EDGE);
    }

}
