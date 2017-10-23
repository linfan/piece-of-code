package com.flin.code.common.utils;

import java.util.Base64;

public class UserTokenValidator {

    public static boolean validate(Long userId, String token) {
        return Base64.getEncoder().encodeToString(userId.toString().getBytes()).equals(token);
    }

}
