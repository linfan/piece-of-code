package com.demo.syntax.controller;

import com.demo.syntax.service.JavaSyntaxHighlighter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

@Controller
@RequestMapping(value = "/api/highlight")
public class SyntaxHighlightController {

    private static Logger log = LoggerFactory.getLogger(SyntaxHighlightController.class);

    @Autowired
    private JavaSyntaxHighlighter syntaxHighlighter;

    @RequestMapping(value="/java", method=RequestMethod.POST)
    public @ResponseBody String handleFileUpload(@RequestParam("file") MultipartFile file) throws IOException {
        log.info("Received syntax highlight request");
        String code = new String(file.getBytes());
        return syntaxHighlighter.beautify(code);
    }

}
