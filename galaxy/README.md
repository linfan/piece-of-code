# 演示Google Test单元测试和Doxygen代码文档

## 场景问题：银河系商人指南

给定一些输入信息，其中包含某种`银河数字`和`罗马数字`的对应关系，以及某些`货币替代物`与`通用货币Credit`之间的价值换算关系，并提出几个关于数值转换或货币转换的问题，格式举例如下：

```
glob is I
prok is V
pish is X
tegj is L
glob glob Silver is 34 Credits
glob prok Gold is 57800 Credits
pish pish Iron is 3910 Credits
how much is pish tegj glob glob ?
how many Credits is glob prok Silver ?
how many Credits is glob prok Gold ?
how many Credits is glob prok Iron ?
how much wood could a woodchuck chuck if a woodchuck could chuck wood ?
```

前4行类型的输入表示罗马数字对应的特殊表示标记。第5-7行类型的输入表示特定物品（例子中是Silver、Gold和Iron）代表的Credit价值。

提问分为两类。第8行是以"how much"开头的第一类，即特定数字标记所表示的真实数值为多少。第9-11行是以"how many"开头的第二类，即特定数量的货币替代物等价于多少Credit。且可能存在一些不符合输入信息范围的提问，如第12行。

这些信息和提问出现的顺序是乱序的，即可能提问出现在信息前面，几种类型的信息和提问也可能会相互穿插出现。

输出按提问顺序的依次回答，对于非法的提问，一律回答“I have no idea what you are talking about”。例如对上述输入的输出格式应为：

```
pish tegj glob glob is 42
glob prok Silver is 68 Credits
glob prok Gold is 57800 Credits
glob prok Iron is 782 Credits
I have no idea what you are talking about
```

## 构建方法

### 编译测试框架库

项目使用`gtest`（[Google C++ Testing Framework](https://github.com/google/googletest)）作为单元测试框架。

由于不同操作系统所需的框架库二进制格式存在差异，同时为了减少目录体积，代码仓库中未包含框架库的二进制文件和头文件。

以使用`Make`工具的Linux操作系统为例，可使用以下命令获得所需文件。（`$REPO_ROOT`表示此代码仓库根目录）

```
git clone https://github.com/google/googletest.git
cd googletest/make
make

mkdir $REPO_ROOT/galaxy/unittest/{include,lib}
cp -r include/gtest $REPO_ROOT/galaxy/unittest/include/
cp gtest_main.a $REPO_ROOT/galaxy/unittest/lib/libgtest.a
```

### 编译源代码并运行单元测试

简便的方式：

```
$ make
```

这个操作会将编译出的二进制文件放到`./bin`目录，可以进入该目录执行执行相应程序。

```
$ cd ./bin
$ vim input-file.txt        # 编写一个输入文件
$ ./main input-file.txt     # 回答指定输入文件中的提问
$ ./test_main               # 手工执行单元测试程序
```

### 生成Doxygen代码文档

> 这个操作需要本地环境预装有Doxygen命令行工具

```
$ make doxygen
```

生成的文档首页为`./doc/html/index.html`，可以使用浏览器直接打开。

### 在Makefile中的其他任务

```
$ make ctags       # 生成源代码的ctags标签文件
$ make clean       # 清除生成的二进制文件和Object中间文件
$ make distclean   # 清除所有生成的文件，包括cscope和ctags标签文件
```

### 运行演示脚本

```
$ cd ./demo
$ ./demo_1    # 使用原始的输入示例演示
$ ./demo_2    # 使用更复杂的输入示例演示
```

> 关于系统和编译器版本：
> 
> - 由于代码中使用了如`for_each宏`和`lambda表达式`等`c++11`语法，低于`4.7版本`的g++编译器将会有编译错误。
> - 该示例在Linux下的g++`4.7.2版本`（使用libgcc`3.4版本`）和clang++`3.3版本`下验证通过，对于其他操作系统或更高版本的编译器应该兼容。

## 代码设计


整体代码树结构如下：

```
├── Makefile
├── bin/
├── doc/
├── src/
│   ├── obj/
│   ├── Makefile
│   ├── main.cc
│   ├── doc.h
│   ├── GalaxyTranslater.cc
│   ├── GalaxyTranslater.h
│   ├── InputReader.cc
│   ├── InputReader.h
│   ├── OutputCalculator.cc
│   ├── OutputCalculator.h
│   ├── RomanTranslater.cc
│   └── RomanTranslater.h
├── unittest/
│   ├── include/
│   ├── lib/
│   ├── obj/
│   ├── Makefile
│   ├── test_main.cc
│   ├── test_GalaxyTranslater.cc
│   ├── test_InputReader.cc
│   ├── test_OutputCalculator.cc
│   └── test_RomanTranslater.cc
└── demo/
    ├── demo_1
    └── demo_2
```

主要用到的类：

- `InputReader`：解析输入文件，产生银河系数字标识的映射表、货币替代物的映射表和问题列表
- `OutputCalculator`：根据`InputReader`解析的结果，计算提问的答案，并产生输出内容
- `GalaxyTranslater`：用于将银河系数字转换为罗马数字的工具类，在`OutputCalculator`中使用
- `RomanTranslater`：用于将罗马数字转换为阿拉伯数字的工具类，在`OutputCalculator`中使用
- `InputInformation`：用于封装记录信息的结构体，在`InputReader`和`OutputCalculator`之间传递信息
