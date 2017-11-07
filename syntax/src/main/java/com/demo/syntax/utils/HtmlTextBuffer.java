package com.demo.syntax.utils;

public class HtmlTextBuffer {

    private StringBuffer buf = new StringBuffer();

    public void beginCodeBlock() {
        buf.append("<ol><li>");
    }

    public void endCodeBlock() {
        buf.append("</li></ol>");
    }

    public void newLine() {
        buf.append("</li><li>");
    }

    public void newLineWithStyle(String style) {
        buf.append(String.format("</div></li><li><div class=\"%s\">", style));
    }

    public void putDivClassLeftPart(int offset, String style) {
        buf.insert(buf.length() - offset, String.format("<div class=\"%s\">", style));
    }

    public void putDivClassRightPart() {
        buf.append("</div>");
    }

    public void putDivClass(int offset, String style) {
        putDivClassLeftPart(offset, style);
        putDivClassRightPart();
    }

    public void putChar(char c) {
        buf.append(c);
    }

    public void putLeftArrow() {
        buf.append("&lt;");
    }

    public void putRightArrow() {
        buf.append("&gt;");
    }

    public void putSpace(boolean shouldEscape) {
        if (shouldEscape) {
            buf.append("&nbsp;");
        } else {
            buf.append(" ");
        }
    }

    public void putTabIndent() {
        buf.append("&nbsp;&nbsp;&nbsp;&nbsp;");
    }

    public String getHtml() {
        return buf.toString();
    }
}
