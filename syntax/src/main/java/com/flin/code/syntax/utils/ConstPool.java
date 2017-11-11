package com.flin.code.syntax.utils;

import com.google.common.collect.ImmutableSet;

import java.util.Set;

public class ConstPool {

    // 样式名称
    public static final String SINGLE_LINE_COMMENT_STYLE = "single-line-comment-style";
    public static final String MULTI_LINE_COMMENT_STYLE = "multi-line-comment-style";
    public static final String SINGLE_QUOTE_STYLE = "single-quote-style";
    public static final String DOUBLE_QUOTE_STYLE = "double-quote-style";
    public static final String LITERAL_STYLE = "literal-style";
    public static final String KEYWORD_STYLE = "keyword-style";
    public static final String PRIMITIVE_TYPE_STYLE = "primitive-type-style";
    public static final String CONSTANT_STYLE = "constant-style";
    public static final String NON_PRIMITIVE_TYPE_STYLE = "non-primitive-type-style";
    public static final String DIGITAL_STYLE = "digital-style";

    // 字面常量
    public static final Set<String> LITERALS = ImmutableSet.of("null", "true", "false");
    // 关键词
    public static final Set<String> KEYWORDS = ImmutableSet.of("abstract", "break", "case",
            "catch", "class", "const", "continue", "default", "do", "else",
            "extends", "final", "finally", "for", "goto", "if", "implements", "import",
            "instanceof", "interface", "native", "new", "package", "private",
            "protected", "public", "return", "static", "strictfp", "super",
            "switch", "synchronized", "this", "throw", "throws", "transient",
            "try", "volatile", "while");
    // 原始数据类型
    public static final Set<String> PRIMITIVE_TYPES = ImmutableSet.of("boolean", "char", "byte",
            "short", "int", "long", "float", "double", "void");

}
