package com.flin.code.syntax.service;

import org.junit.Test;

import static org.junit.Assert.*;

public class JavaSyntaxHighlighterTest {

    private JavaSyntaxHighlighter highlighter = new JavaSyntaxHighlighter();

    @Test
    public void should_able_to_handle_literal_style() throws Exception {
        String codeStr = "what you said was true";
        String highlightedStr = "<ol><li>what you said was <div class=\"literal-style\">true</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_keyword_and_primitive_style() throws Exception {
        String codeStr = "public void main() { ... }";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">public</div> <div class=\"primitive-type-style\">void</div> main() { ... }</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_const_and_number_style() throws Exception {
        String codeStr = "final int PI = 3.1415;";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">final</div> <div class=\"primitive-type-style\">int</div> <div class=\"constant-style\">PI</div> = <div class=\"digital-style\">3.1415</div>;</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_many_kind_of_number_style() throws Exception {
        String codeStr = "+123 -456 3.1415 2e4 3E-5 .99";
        String highlightedStr = "<ol><li><div class=\"digital-style\">+123</div> <div class=\"digital-style\">-456</div> <div class=\"digital-style\">3.1415</div> <div class=\"digital-style\">2e4</div> <div class=\"digital-style\">3E-5</div> <div class=\"digital-style\">.99</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_non_primitive_style() throws Exception {
        String codeStr = "class Demo { ... }";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">class</div> <div class=\"non-primitive-type-style\">Demo</div> { ... }</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_quote_style() throws Exception {
        String codeStr = "\"in \'double\' quote\" \'in \"single\" quote\'";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"in 'double' quote\"</div> <div class=\"single-quote-style\">'in \"single\" quote'</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_comment_style() throws Exception {
        String codeStr = "a /*line*/ with // comment's word\nnext line";
        String highlightedStr = "<ol><li>a <div class=\"multi-line-comment-style\">/*line*/</div> with <div class=\"single-line-comment-style\">// comment's word</div></li><li>next line</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_comment_style_cross_lines() throws Exception {
        String codeStr = "here is /* some \n comment that \r\n has many lines */ util here";
        String highlightedStr = "<ol><li>here is <div class=\"multi-line-comment-style\">/* some </div></li><li><div class=\"multi-line-comment-style\"> comment that </div></li><li><div class=\"multi-line-comment-style\"> has many lines */</div> util here</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_special_symbols() throws Exception {
        String codeStr = "\tbook <the little prince> is \\good";
        String highlightedStr = "<ol><li>&nbsp;&nbsp;&nbsp;&nbsp;book &lt;the little prince&gt; is \\good</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_continue_spaces() throws Exception {
        String codeStr = "there are  spaces   here";
        String highlightedStr = "<ol><li>there are &nbsp;spaces &nbsp;&nbsp;here</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_slash_in_quote() throws Exception {
        String codeStr = "\"\\n \\t \\\\ \\\" \\'\" '\\\\' '\\'' '\\\\' end";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"\\n \\t \\\\ \\\" \\'\"</div> <div class=\"single-quote-style\">'\\\\'</div> <div class=\"single-quote-style\">'\\''</div> <div class=\"single-quote-style\">'\\\\'</div> end</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_digital_in_quote_and_comment() throws Exception {
        String codeStr = "\"[.*[0-9].*]\" match '2017' /*comment 007*/";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"[.*[0-9].*]\"</div> match <div class=\"single-quote-style\">'2017'</div> <div class=\"multi-line-comment-style\">/*comment 007*/</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

}
