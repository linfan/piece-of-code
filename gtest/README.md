# GTest官方Demo中文译注

`GTest`（[Google C++ Testing Framework](https://github.com/google/googletest)）测试框架官方测试样例的中文译注版。

## 编译测试框架库

代码仓库中未包含测试框架库的二进制文件和头文件，由于不同操作系统所需的框架库二进制格式存在差异，使用前建议通过官方仓库直接编译所需的框架库。

以使用`Make`工具的Linux操作系统为例，具体操作如下（`$REPO_ROOT`表示此代码仓库根目录）：

1. 在当前目录创建`include`和`lin`目录

```
mkdir $REPO_ROOT/{include,lib}
```

2. 获取`googletest`仓库源代码

```
git clone https://github.com/google/googletest.git
```

3. 编译并拷贝`gtest`文件

```
cd googletest/make
make
cp -r include/gtest $REPO_ROOT/include/
cp gtest_main.a $REPO_ROOT/lib/
```

4. 编译并拷贝`gmock`文件

```
cd googlemock/make
make
cp -r include/gmock $REPO_ROOT/include/
cp gmock_main.a $REPO_ROOT/lib/
```

## 编译并运行单元测试示例

所有示例在`release-1.8.0`版本GTest下验证，且应当适用于`1.x`系列的更高版本。

使用`run.sh`脚本自动修改`Makefile`中的构建目标，并运行测试，参数为1至11之间的一个数字，分别表示执行demo01~demo11示例。例如：

```
./run.sh 1
```

* 示例一：
> 使用`TEST()`和`EXPECT_XX()`方法测试全局函数

* 示例二：
> 使用`TEST()`和`EXPECT_XX()`方法测试自定义类型的对象

* 示例三：
> 使用`Test类型`和`TEST_F()`方法测试自定义类型的对象

* 示例四：
> 证实`EXPECT_XX()`方法会实际执行参数中的表达式，并可能因此产生副作用

* 示例五：
> 演示通过继承实现通用的测试类，以及基于时间的测试验证

* 示例六：
> 使用`TYPED_TEST`和`TYPED_TEST_P`实现基于类型的数据驱动测试

* 示例七：
> 使用`TEST_P`实现基于类型的数据驱动测试

* 示例八：
> 使用`TEST_P`实现基于类型的数据驱动测试的例子扩展

* 示例九：
> 使用事件监听器替换测试结果的输出

* 示例十：
> 使用事件监听器为每个测试增加额外检查

* 示例十一：
> 使用GMock创建测试桩
