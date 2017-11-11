package com.flin.code.bean;

public class Journey {

    public double beginPos;   // 简便起见，使用public成员，省略getter/setter
    public double endPos;

    public Journey(double beginPos, double endPos) {
        this.beginPos = beginPos;
        this.endPos = endPos;
    }

}
