package com.flin.code.syntax.enums;

public enum SyntaxState {
    STATE_TEXT,                // 普通文本
    STATE_DIGITAL,             // 数值文本
    STATE_SINGLE_QUOTE,        // 单引号内
    STATE_DOUBLE_QUOTE,        // 双引号内
    STATE_LINE_END_COMMENT,    // 行末注释
    STATE_MULTI_LINE_COMMENT   // 多行注释
}
