package com.flin.code.common.utils;

import java.util.UUID;

public class UuidGenerator {

    public static String gen() {
        return UUID.randomUUID().toString();
    }

}
