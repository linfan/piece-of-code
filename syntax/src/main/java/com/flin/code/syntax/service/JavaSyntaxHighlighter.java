package com.flin.code.syntax.service;

import com.flin.code.syntax.utils.HtmlTextBuffer;
import com.flin.code.syntax.enums.SyntaxState;
import com.flin.code.syntax.utils.ConstPool;
import com.google.common.collect.ImmutableSet;
import com.google.common.collect.Lists;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class JavaSyntaxHighlighter {

    private HtmlTextBuffer buf;
    private SyntaxState state;
    private List<String> fields;
    private List<String> methods;
    private String fmCandidate;

    /**
     * 当前位置的"/"是真正的反斜杠(而不是转译符)
     */
    private boolean isRealSlash;
    /**
     * 当前位置是在变量或字段的赋值内容里
     */
    private boolean isAssignment;
    /**
     * 当前位置的小括号层级
     */
    private int parenthesisLevel;
    /**
     * 当前位置的大括号层级
     */
    private int braceLevel;

    public String beautify(String code) {
        buf = new HtmlTextBuffer();
        state = SyntaxState.STATE_TEXT;
        fields = Lists.newArrayList();
        methods = Lists.newArrayList();
        fmCandidate = "";
        isRealSlash = false;
        isAssignment = false;
        parenthesisLevel = 0;
        braceLevel = 0;
        long totalSize = code.length();
        int identifierLength = 0;
        char previousChar, currentChar, nextChar;

        buf.beginCodeBlock();
        for (int i = 0; i <= totalSize; i++) {
            previousChar = (i > 0) ? code.charAt(i - 1) : 0;
            currentChar = (i < totalSize) ? code.charAt(i) : 0;
            nextChar = (i < totalSize - 1) ? code.charAt(i + 1) : 0;

            // 单独处理数字文本
            if (reachDigitalEdge(identifierLength, currentChar, nextChar)) {
                state = SyntaxState.STATE_DIGITAL;
            }
            // 移动到标识符边界
            if (notYetReachIdentifierEdge(currentChar)) {
                buf.putChar(currentChar);
                ++identifierLength;
                continue;
            }
            // 标识符高亮
            state = highlightTextAndDigital(code.substring(i - identifierLength, i), identifierLength);
            identifierLength = 0;

            // 特殊字符和字符串、注释处理
            handleSpecialCharacter(previousChar, currentChar, nextChar, i > 0);
        }
        if (state == SyntaxState.STATE_LINE_END_COMMENT) {
            buf.putDivClassRightPart();
        }
        buf.endCodeBlock();

        return highlightFieldsAndMethods(buf.getHtml());
    }

    private String highlightFieldsAndMethods(String html) {
        html = fields.stream().reduce(html, (text, field) ->
            text.replaceAll("\\b" + field + "\\b", HtmlTextBuffer.withStyle(field, ConstPool.CLASS_FIELD_STYLE)));
        html = methods.stream().reduce(removeDivInDiv(html), (text, method) ->
            text.replaceAll("\\b" + method + "\\b", HtmlTextBuffer.withStyle(method, ConstPool.CLASS_METHOD_STYLE)));
        return removeDivInDiv(html);
    }

    private void handleSpecialCharacter(char previousChar, char currentChar, char nextChar, boolean isNotHeadChar) {
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
                if (state == SyntaxState.STATE_SINGLE_QUOTE || state == SyntaxState.STATE_DOUBLE_QUOTE) {
                    isRealSlash = !isRealSlash && (previousChar == '\\');
                }
                break;
            case '\"':
                buf.putChar('\"');
                if (state == SyntaxState.STATE_TEXT) {
                    state = SyntaxState.STATE_DOUBLE_QUOTE;
                    buf.putDivClassLeftPart("\"".length(), ConstPool.DOUBLE_QUOTE_STYLE);
                } else if (isEndOfDoubleQuote(previousChar)) {
                    state = SyntaxState.STATE_TEXT;
                    buf.putDivClassRightPart();
                }
                break;
            case '\'':
                buf.putChar('\'');
                if (state == SyntaxState.STATE_TEXT) {
                    state = SyntaxState.STATE_SINGLE_QUOTE;
                    buf.putDivClassLeftPart("\'".length(), ConstPool.SINGLE_QUOTE_STYLE);
                } else if (isEndOfSingleQuote(previousChar)) {
                    state = SyntaxState.STATE_TEXT;
                    buf.putDivClassRightPart();
                }
                break;
            case '{':
                buf.putChar('{');
                if (!isRawTextSyntaxStatus()) {
                    braceLevel++;
                }
                break;
            case '}':
                buf.putChar('}');
                if (!isRawTextSyntaxStatus()) {
                    braceLevel--;
                }
                break;
            case '*':
                buf.putChar('*');
                if (state == SyntaxState.STATE_TEXT && isNotHeadChar && previousChar == '/') {
                    buf.putDivClassLeftPart("/*".length(), ConstPool.MULTI_LINE_COMMENT_STYLE);
                    state = SyntaxState.STATE_MULTI_LINE_COMMENT;
                }
                break;
            case '/':
                buf.putChar('/');
                if (state == SyntaxState.STATE_TEXT && isNotHeadChar && previousChar == '/') {
                    buf.putDivClassLeftPart("//".length(), ConstPool.SINGLE_LINE_COMMENT_STYLE);
                    state = SyntaxState.STATE_LINE_END_COMMENT;
                } else if (state == SyntaxState.STATE_MULTI_LINE_COMMENT && isNotHeadChar && previousChar == '*') {
                    buf.putDivClassRightPart();
                    state = SyntaxState.STATE_TEXT;
                }
                break;
            case '(':
                buf.putChar('(');
                if (!isRawTextSyntaxStatus()) {
                    if (!fmCandidate.isEmpty() && isInClassButOutOfMethod() && notMethodParameters() && !isAssignment) {
                        methods.add(fmCandidate);
                        fmCandidate = "";
                    }
                    parenthesisLevel++;
                }
                break;
            case ')':
                buf.putChar(')');
                if (!isRawTextSyntaxStatus()) {
                    parenthesisLevel--;
                }
                break;
            case ';':
            case ',':
                buf.putChar(currentChar);
                if (!isRawTextSyntaxStatus()) {
                    if (!fmCandidate.isEmpty() && isInClassButOutOfMethod() && notMethodParameters() && !isAssignment) {
                        fields.add(fmCandidate);
                        fmCandidate = "";
                    }
                    isAssignment = false;
                }
                break;
            case '=':
                buf.putChar('=');
                if (nextChar != '=' && !ImmutableSet.of('=', '>', '<', '!').contains(previousChar)) {
                    if (!fmCandidate.isEmpty() && isInClassButOutOfMethod()) {
                        fields.add(fmCandidate);
                        fmCandidate = "";
                    }
                    isAssignment = true;
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

    private SyntaxState highlightTextAndDigital(String identifier, int identifierLength) {
        if (identifierLength > 0) {
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
                } else if (identifier.charAt(0) == '@') {
                    buf.putDivClass(identifierLength, ConstPool.ANNOTATION_STYLE);
                } else if (isInClassButOutOfMethod() && isLegalVariableName(identifier)) {
                    fmCandidate = identifier;
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

    private String removeDivInDiv(String html) {
        // Not a perfect solution, it assume string inside div dose not content '<' character
        return html.replaceAll("(<div [^>]+>[^<]+)(?!</div>)([^<]+)<div [^>]+>(.+?)</div>", "$1$2$3");
    }

    private boolean notMethodParameters() {
        return parenthesisLevel == 0;
    }

    private boolean isInClassButOutOfMethod() {
        return braceLevel == 1;
    }

    private boolean isRawTextSyntaxStatus() {
        return state == SyntaxState.STATE_LINE_END_COMMENT ||
            state == SyntaxState.STATE_MULTI_LINE_COMMENT ||
            state == SyntaxState.STATE_SINGLE_QUOTE ||
            state == SyntaxState.STATE_DOUBLE_QUOTE ;
    }

    private boolean isEndOfSingleQuote(char previousChar) {
        return state == SyntaxState.STATE_SINGLE_QUOTE && (previousChar != '\\' || isRealSlash);
    }

    private boolean isEndOfDoubleQuote(char previousChar) {
        return state == SyntaxState.STATE_DOUBLE_QUOTE && (previousChar != '\\' || isRealSlash);
    }

    private boolean reachDigitalEdge(int identifierLength, char currentChar, char nextChar) {
        return identifierLength == 0 && state == SyntaxState.STATE_TEXT && isDigitalStartChars(currentChar, nextChar);
    }

    private boolean isLegalVariableName(String str) {
        return str.matches("[a-zA-Z]+[0-9a-zA-Z_]*");
    }

    private boolean notYetReachIdentifierEdge(char c) {
        return c != 0 &&
            (Character.isJavaIdentifierPart(c) || c == '@' || (state == SyntaxState.STATE_DIGITAL && isDigitalChar(c)));
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
