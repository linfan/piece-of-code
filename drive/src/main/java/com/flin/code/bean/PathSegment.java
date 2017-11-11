package com.flin.code.bean;

public class PathSegment {

    public int beginPos;      // 简便起见，使用public成员，省略getter/setter
    public int endPos;
    public int speed;

    public PathSegment(int beginPos, int endPos, int speed) {
        this.beginPos = beginPos;
        this.endPos = endPos;
        this.speed = speed;
    }
}
