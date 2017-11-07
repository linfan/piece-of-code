package com.demo.syntax.service;

import com.demo.syntax.utils.HtmlTextBuffer;
import com.demo.syntax.enums.SyntaxState;
import com.demo.syntax.utils.ConstPool;
import com.google.common.collect.ImmutableSet;
import org.springframework.stereotype.Service;

@Service
public class JavaSyntaxHighlighter {

    public String beautify(String code) {

        HtmlTextBuffer buf = new HtmlTextBuffer();
        int identifierLength = 0;
        char previousChar, currentChar, nextChar;
        boolean doubleEscape = false;
        SyntaxState state = SyntaxState.STATE_TEXT;
        long totalSize = code.length();

        buf.beginCodeBlock();
        for (int i = 0; i <= totalSize; i++) {
            previousChar = (i > 0) ? code.charAt(i - 1) : 0;
            currentChar = (i < totalSize) ? code.charAt(i) : 0;
            nextChar = (i < totalSize - 1) ? code.charAt(i + 1) : 0;

            // 单独处理数字文本
            if (reachDigitalEdge(identifierLength, currentChar, nextChar, state)) {
                state = SyntaxState.STATE_DIGITAL;
            }
            // 移动到标识符边界
            if (notYetReachIdentifierEdge(currentChar, state)) {
                buf.putChar(currentChar);
                ++identifierLength;
                continue;
            }
            // 标识符高亮
            state = highlightTextAndDigital(code.substring(i - identifierLength, i), buf, identifierLength, state);
            identifierLength = 0;

            // 特殊字符和字符串、注释处理
            switch (currentChar) {
                case '<':
                    buf.putLeftArrow();
                    break;
                case '>':
                    buf.putRightArrow();
                    break;
                case ' ':
                    buf.putSpace(previousChar == ' ');
                    break;
                case '\t':
                    buf.putTabIndent();
                    break;
                case '\\':
                    buf.putChar('\\');
                    if (previousChar == '\\' && ((state == SyntaxState.STATE_DOUBLE_QUOTE && nextChar == '\"')
                            || (state == SyntaxState.STATE_SINGLE_QUOTE && nextChar == '\''))) {
                        doubleEscape = true;
                    }
                    break;
                case '\"':
                    buf.putChar('\"');
                    if (state == SyntaxState.STATE_TEXT) {
                        state = SyntaxState.STATE_DOUBLE_QUOTE;
                        buf.putDivClassLeftPart("\"".length(), ConstPool.DOUBLE_QUOTE_STYLE);
                    } else if (state == SyntaxState.STATE_DOUBLE_QUOTE && (previousChar != '\\' || doubleEscape)) {
                        state = SyntaxState.STATE_TEXT;
                        buf.putDivClassRightPart();
                        doubleEscape = false;
                    }
                    break;
                case '\'':
                    buf.putChar('\'');
                    if (state == SyntaxState.STATE_TEXT) {
                        state = SyntaxState.STATE_SINGLE_QUOTE;
                        buf.putDivClassLeftPart("\'".length(), ConstPool.SINGLE_QUOTE_STYLE);
                    } else if (state == SyntaxState.STATE_SINGLE_QUOTE && (previousChar != '\\' || doubleEscape)) {
                        state = SyntaxState.STATE_TEXT;
                        buf.putDivClassRightPart();
                        doubleEscape = false;
                    }
                    break;
                case '*':
                    buf.putChar('*');
                    if (state == SyntaxState.STATE_TEXT && i > 0 && previousChar == '/') {
                        buf.putDivClassLeftPart("/*".length(), ConstPool.MULTI_LINE_COMMENT_STYLE);
                        state = SyntaxState.STATE_MULTI_LINE_COMMENT;
                    }
                    break;
                case '/':
                    buf.putChar('/');
                    if (state == SyntaxState.STATE_TEXT && i > 0 && previousChar == '/') {
                        buf.putDivClassLeftPart("//".length(), ConstPool.SINGLE_LINE_COMMENT_STYLE);
                        state = SyntaxState.STATE_LINE_END_COMMENT;
                    } else if (state == SyntaxState.STATE_MULTI_LINE_COMMENT && i > 0 && previousChar == '*') {
                        buf.putDivClassRightPart();
                        state = SyntaxState.STATE_TEXT;
                    }
                    break;
                case '\n':
                    if (state == SyntaxState.STATE_LINE_END_COMMENT) {
                        buf.putDivClassRightPart();
                        state = SyntaxState.STATE_TEXT;
                    }
                    if (state == SyntaxState.STATE_MULTI_LINE_COMMENT) {
                        buf.newLineWithStyle(ConstPool.MULTI_LINE_COMMENT_STYLE);
                    } else {
                        buf.newLine();
                    }
                    break;
                case '\r':
                case 0:
                    break;
                default:
                    buf.putChar(currentChar);
            }
        }
        if (state == SyntaxState.STATE_LINE_END_COMMENT)
            buf.putDivClassRightPart();
        buf.endCodeBlock();

        return buf.getHtml();
    }

    boolean reachDigitalEdge(int identifierLength, char currentChar, char nextChar, SyntaxState state) {
        return identifierLength == 0 && state == SyntaxState.STATE_TEXT && isDigitalStartChars(currentChar, nextChar);
    }

    private SyntaxState highlightTextAndDigital(String substring, HtmlTextBuffer buf, int identifierLength, SyntaxState state) {
        if (identifierLength > 0) {
            String identifier = substring;
            if (state == SyntaxState.STATE_TEXT) {
                if (ConstPool.LITERALS.contains(identifier)) {
                    buf.putDivClass(identifierLength, ConstPool.LITERAL_STYLE);
                } else if (ConstPool.KEYWORDS.contains(identifier)) {
                    buf.putDivClass(identifierLength, ConstPool.KEYWORD_STYLE);
                } else if (ConstPool.PRIMITIVE_TYPES.contains(identifier)) {
                    buf.putDivClass(identifierLength, ConstPool.PRIMITIVE_TYPE_STYLE);
                } else if (identifier.equals(identifier.toUpperCase())) {
                    buf.putDivClass(identifierLength, ConstPool.CONSTANT_STYLE);
                } else if (Character.isUpperCase(identifier.charAt(0))) {
                    buf.putDivClass(identifierLength, ConstPool.NON_PRIMITIVE_TYPE_STYLE);
                }
            }
            if (state == SyntaxState.STATE_DIGITAL) {
                if (hasAtLeastOneNum(identifier)) {
                    buf.putDivClass(identifierLength, ConstPool.DIGITAL_STYLE);
                }
                state = SyntaxState.STATE_TEXT;
            }
        }
        return state;
    }

    private boolean notYetReachIdentifierEdge(char currentChar, SyntaxState state) {
        return currentChar != 0 && (Character.isJavaIdentifierPart(currentChar) ||
                state == SyntaxState.STATE_DIGITAL && isDigitalChar(currentChar));
    }

    private boolean hasAtLeastOneNum(String str) {
        return str.matches(".*[0-9].*");
    }

    private boolean isDigitalChar(char c) {
        return ImmutableSet.of('-', '+', '.', 'e', 'E').contains(c) || (c >= '0' && c <= '9');
    }

    private boolean isDigitalStartChars(char c1, char c2) {
        return (ImmutableSet.of('-', '+', '.').contains(c1) && (c2 >= '0' && c2 <= '9')) || (c1 >= '0' && c1 <= '9');
    }

}
