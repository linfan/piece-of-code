#include <limits.h>
#include <time.h>
#include "gtest/gtest.h"
#include "demo03.h"
#include "demo05.h"

/* 示例五：
 * 演示通过继承实现通用的测试类，以及基于时间的测试验证
 *
 * 在这个例子中，我们希望所有的用例在5秒钟内完成，超时的用例会被标记为失败
 * 在 TearDown() 方法中也可以使用 EXPECT_XX() 检验
*/

// QuickTest类型作为所有其他测试类的基类
// 它在 SetUp() 和 TearDown() 方法中包含了对执行时间的验证
class QuickTest : public testing::Test {
protected:
    // 在每个用例开始前运行
    virtual void SetUp() {
        start_time_ = time(NULL);
    }

    // 在每个用例结束后运行，检查是否超时
    virtual void TearDown() {
        const time_t end_time = time(NULL);
        EXPECT_TRUE(end_time - start_time_ <= 5) << "The test took too long.";
    }

    // The UTC time (in seconds) when the test starts
    time_t start_time_;
};


// 继承 QuickTest 的测试类型
class IntegerFunctionTest : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
};


// Now we can write tests in the IntegerFunctionTest test case.

// Tests Factorial()
TEST_F(IntegerFunctionTest, Factorial) {
    // Tests factorial of negative numbers.
    EXPECT_EQ(1, Factorial(-5));
    EXPECT_EQ(1, Factorial(-1));
    EXPECT_GT(Factorial(-10), 0);

    // Tests factorial of 0.
    EXPECT_EQ(1, Factorial(0));

    // Tests factorial of positive numbers.
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(6, Factorial(3));
    EXPECT_EQ(40320, Factorial(8));
}


// Tests IsPrime()
TEST_F(IntegerFunctionTest, IsPrime) {
    // Tests negative input.
    EXPECT_FALSE(IsPrime(-1));
    EXPECT_FALSE(IsPrime(-2));
    EXPECT_FALSE(IsPrime(INT_MIN));

    // Tests some trivial cases.
    EXPECT_FALSE(IsPrime(0));
    EXPECT_FALSE(IsPrime(1));
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));

    // Tests positive input.
    EXPECT_FALSE(IsPrime(4));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_FALSE(IsPrime(6));
    EXPECT_TRUE(IsPrime(23));
}


// 另一个继承自 QuickTest 的测试类，它会获得在 QuickTest 类型中已经定义的能力
// 并在此基础上加以扩展
class QueueTest : public QuickTest {
protected:

    // 覆写 SetUp() 方法
    virtual void SetUp() {
        // 首先记得要调用父类的SetUp()方法
        QuickTest::SetUp();
        // 然后执行其他的初始化操作
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }

    // 使用默认继承的 QuickTest::TearDown() 方法，无需显示声明或覆写

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};


// Now, let's write tests using the QueueTest fixture.

// Tests the default constructor.
TEST_F(QueueTest, DefaultConstructor) {
    EXPECT_EQ(0u, q0_.Size());
}

// Tests Dequeue().
TEST_F(QueueTest, Dequeue) {
    int* n = q0_.Dequeue();
    EXPECT_TRUE(n == NULL);

    n = q1_.Dequeue();
    EXPECT_TRUE(n != NULL);
    EXPECT_EQ(1, *n);
    EXPECT_EQ(0u, q1_.Size());
    delete n;

    n = q2_.Dequeue();
    EXPECT_TRUE(n != NULL);
    EXPECT_EQ(2, *n);
    EXPECT_EQ(1u, q2_.Size());
    delete n;
}
