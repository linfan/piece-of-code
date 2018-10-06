package com.flin.code.syntax.service;

import org.junit.Test;

import static org.junit.Assert.*;

public class JavaSyntaxHighlighterTest {

    private JavaSyntaxHighlighter highlighter = new JavaSyntaxHighlighter();

    @Test
    public void should_able_to_handle_literal_style() {
        String codeStr = "what you said was true";
        String highlightedStr = "<ol><li>what you said was <div class=\"literal-style\">true</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_keyword_and_primitive_style() {
        String codeStr = "public void main() { ... }";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">public</div> <div class=\"primitive-type-style\">"
            + "void</div> main() { ... }</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_const_and_number_style() {
        String codeStr = "final int PI = 3.1415;";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">final</div> <div class=\"primitive-type-style\">"
            + "int</div> <div class=\"constant-style\">PI</div> = <div class=\"digital-style\">3.1415</div>;</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_many_kind_of_number_style() {
        String codeStr = "+123 -456 3.1415 2e4 3E-5 .99";
        String highlightedStr = "<ol><li><div class=\"digital-style\">+123</div> <div class=\"digital-style\">-456</div>"
            + " <div class=\"digital-style\">3.1415</div> <div class=\"digital-style\">2e4</div> "
            + "<div class=\"digital-style\">3E-5</div> <div class=\"digital-style\">.99</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_non_primitive_style() {
        String codeStr = "class Demo { ... }";
        String highlightedStr = "<ol><li><div class=\"keyword-style\">class</div> <div class=\"non-primitive-type-style\">"
            + "Demo</div> { ... }</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_quote_style() {
        String codeStr = "\"in \'double\' quote\" \'in \"single\" quote\'";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"in 'double' quote\"</div> "
            + "<div class=\"single-quote-style\">'in \"single\" quote'</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_comment_style() {
        String codeStr = "a /*line*/ with // comment's word\nnext line";
        String highlightedStr = "<ol><li>a <div class=\"multi-line-comment-style\">/*line*/</div> with "
            + "<div class=\"single-line-comment-style\">// comment's word</div></li><li>next line</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_comment_style_cross_lines() {
        String codeStr = "here is /* some \n comment that \r\n has many lines */ util here";
        String highlightedStr = "<ol><li>here is <div class=\"multi-line-comment-style\">/* some </div></li><li>"
            + "<div class=\"multi-line-comment-style\"> comment that </div></li><li><div class=\"multi-line-comment-style\">"
            + " has many lines */</div> util here</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_special_symbols() {
        String codeStr = "\tbook <the little prince> is \\good";
        String highlightedStr = "<ol><li>&nbsp;&nbsp;&nbsp;&nbsp;book &lt;the little prince&gt; is \\good</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_continue_spaces() {
        String codeStr = "there are  spaces   here";
        String highlightedStr = "<ol><li>there are &nbsp;spaces &nbsp;&nbsp;here</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_slash_in_quote() {
        String codeStr = "\"\\n \\t \\\\ \\\" \\'\" '\\\\' '\\'' '\\\\' end";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"\\n \\t \\\\ \\\" \\'\"</div> "
            + "<div class=\"single-quote-style\">'\\\\'</div> <div class=\"single-quote-style\">'\\''</div> "
            + "<div class=\"single-quote-style\">'\\\\'</div> end</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_digital_in_quote_and_comment() {
        String codeStr = "\"[.*[0-9].*]\" match '2017' /*comment 007*/";
        String highlightedStr = "<ol><li><div class=\"double-quote-style\">\"[.*[0-9].*]\"</div> match "
            + "<div class=\"single-quote-style\">'2017'</div> <div class=\"multi-line-comment-style\">"
            + "/*comment 007*/</div></li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_annotation() {
        String codeStr = "{\n @Autowired\n private SymbolService symbolService;\n\n @Value(\"${demo.enable}\")\n private Boolean enable;";
        String highlightedStr = "<ol><li>{</li><li> <div class=\"annotation-style\">@Autowired</div></li><li>"
            + " <div class=\"keyword-style\">private</div> <div class=\"non-primitive-type-style\">SymbolService</div>"
            + " <div class=\"field-style\">symbolService</div>;</li><li></li><li> <div class=\"annotation-style\">@Value</div>"
            + "(<div class=\"double-quote-style\">\"${demo.enable}\"</div>)</li><li> <div class=\"keyword-style\">private</div>"
            + " <div class=\"non-primitive-type-style\">Boolean</div> <div class=\"field-style\">enable</div>;</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_class_field() {
        String codeStr = "{\n private DemoFactory demoFactory;\n\n DemoService demoService = newDemoService();\n {\n"
            + "Optional.of(demoFactory.demoServer().index());\nCapabilities.newIns(demoService.getServerCapabilities());";
        String highlightedStr = "<ol><li>{</li><li> <div class=\"keyword-style\">private</div> "
            + "<div class=\"non-primitive-type-style\">DemoFactory</div> <div class=\"field-style\">demoFactory</div>;"
            + "</li><li></li><li> <div class=\"non-primitive-type-style\">DemoService</div> <div class=\"field-style\">"
            + "demoService</div> = newDemoService();</li><li> {</li><li><div class=\"non-primitive-type-style\">"
            + "Optional</div>.of(<div class=\"field-style\">demoFactory</div>.demoServer().index());</li><li>"
            + "<div class=\"non-primitive-type-style\">Capabilities</div>.newIns(<div class=\"field-style\">"
            + "demoService</div>.getServerCapabilities());</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }

    @Test
    public void should_able_to_handle_class_method() {
        String codeStr = "{\n private String demoFunc(String text) { }\n void demoCall() { demoFunc(\"text\"); }";
        String highlightedStr = "<ol><li>{</li><li> <div class=\"keyword-style\">private</div> <div class=\"non-primitive-type-style\">"
            + "String</div> <div class=\"method-style\">demoFunc</div>(<div class=\"non-primitive-type-style\">String</div>"
            + " text) { }</li><li> <div class=\"primitive-type-style\">void</div> <div class=\"method-style\">demoCall</div>"
            + "() { <div class=\"method-style\">demoFunc</div>(<div class=\"double-quote-style\">\"text\"</div>); }</li></ol>";
        assertEquals(highlightedStr, highlighter.beautify(codeStr));
    }
}
