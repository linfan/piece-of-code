#include <limits.h>
#include "demo01.h"
#include "gtest/gtest.h"

/* 示例一：
 * 使用 TEST() 和 EXPECT_XX() 方法测试全局函数
 *
 * TEST() 方法的两个参数分别为 测试组名称 和 测试用例名称
 * EXPECT_EQ 验证相等
 * EXPECT_GT 验证数值大于
 * EXPECT_TRUE 验证结果为真
 * EXPECT_FALSE 验证结果为假
*/

// 测试 Factorial() 方法

// Tests factorial of negative numbers.
TEST(FactorialTest, Negative) {
    EXPECT_EQ(1, Factorial(-5));
    EXPECT_EQ(1, Factorial(-1));
    EXPECT_GT(Factorial(-10), 0);
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) {
    EXPECT_EQ(1, Factorial(0));
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(6, Factorial(3));
    EXPECT_EQ(40320, Factorial(8));
}


// 测试 IsPrime() 方法

// Tests negative input.
TEST(IsPrimeTest, Negative) {
    // This test belongs to the IsPrimeTest test case.
    EXPECT_FALSE(IsPrime(-1));
    EXPECT_FALSE(IsPrime(-2));
    EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
    EXPECT_FALSE(IsPrime(0));
    EXPECT_FALSE(IsPrime(1));
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
    EXPECT_FALSE(IsPrime(4));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_FALSE(IsPrime(6));
    EXPECT_TRUE(IsPrime(23));
}
