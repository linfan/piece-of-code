# 演示Java可执行命令行程序

## 场景说明

一条公路，起点是0公里，终点是100公里。被划分为N段，每段有不同的限速。

计算从A公里处开始，到B公里处结束，在不超过限速的情况下，最少需要多少时间完成路程。

**输入：**
1. 第一行为公路划分的段数N
2. 接下来N行，每行三个正整数，分别是起始点，终止点（前后两段一定保证是连续的），和限速值（单位：公里/小时）
3. 紧接是要计算的起始点A，和终止点B

**输出：**
1. 输出为一行，即从A到B需要的最少时间（单位：小时）,精确到小数点后两位


## 运行方法

借助`spring-boot-maven-plugin`插件实现生成可直接执行的jar包。

```bash
$ mvn clean package

$ ls -lh target/drive-1.0-SNAPSHOT.jar
-rwxr--r-- * * * 99K * target/drive-1.0-SNAPSHOT.jar

$ ./target/drive-1.0-SNAPSHOT.jar
...
```
