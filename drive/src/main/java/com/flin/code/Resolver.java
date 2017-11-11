package com.flin.code;

import com.flin.code.bean.Journey;
import com.flin.code.bean.PathSegment;

import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.List;

public class Resolver {

    public double resolve() {

        List<PathSegment> pathSegments = readSegments();  // 首行数据和路径数据
        Journey journey = readJourney();                  // 读取末行的行程数据
        validateSegmentData(pathSegments);                // 校验数据是否相连且覆盖全路段

        double totalTime = pathSegments.stream()
                .map(segment -> calculateTime(journey, segment))  // 计算每段行程用时
                .reduce((a, b) -> a + b).get();                   // 累加所有行程用时

        showResult(totalTime);                            // 打印结果，精确到小数点2位
        return totalTime;
    }

    private double calculateTime(Journey journey, PathSegment segment) {
        if (segment.beginPos > journey.beginPos && segment.endPos < journey.endPos)
            return (segment.endPos - segment.beginPos) * (1.0 / segment.speed);
        if (segment.beginPos < journey.beginPos && segment.endPos > journey.endPos)
            return (journey.endPos - journey.beginPos) * (1.0 / segment.speed);
        else if (segment.beginPos < journey.beginPos && segment.endPos > journey.beginPos && segment.endPos < journey.endPos)
            return (segment.endPos - journey.beginPos) * (1.0 / segment.speed);
        else if (segment.beginPos > journey.beginPos && segment.beginPos < journey.endPos && segment.endPos > journey.endPos)
            return (journey.endPos - segment.beginPos) * (1.0 / segment.speed);
        else
            return 0;
    }

    private void showResult(double totalTime) {
        double roundedTotalTime = ((int)(totalTime * 100 + 0.5) / 100.0);
        System.out.println(String.format("%.2f", roundedTotalTime));
    }

    List<PathSegment> readSegments() {
        System.out.println("Input how many segments in total (format: <count>):");
        int size = Integer.valueOf(System.console().readLine());
        System.out.println("Input speed limit for each segment (format: <begin> <end> <speed>):");
        List segmentList = new ArrayList();
        for (int i = 0; i < size; i++) {
            String[] seg = System.console().readLine().split("\\W+");
            segmentList.add(new PathSegment(Integer.valueOf(seg[0]),
                    Integer.valueOf(seg[1]), Integer.valueOf(seg[2])));
        }
        return segmentList;
    }

    Journey readJourney() {
        System.out.println("Input begin and end pos (format: <begin> <end>):");
        String[] jrn = System.console().readLine().split("\\W+");
        return new Journey(Double.valueOf(jrn[0]), Double.valueOf(jrn[1]));
    }

    void validateSegmentData(List<PathSegment> pathSegments) {
        if (pathSegments.get(0).beginPos != 0 || pathSegments.get(pathSegments.size() - 1).endPos != 100)
            throw new InvalidParameterException("segments does not cover all path");
        int lastEndPos = 0;
        for (PathSegment segment : pathSegments) {
            if (segment.beginPos != lastEndPos)
                throw new InvalidParameterException("segment end and begin position not match");
            lastEndPos = segment.endPos;
        }
    }
}
