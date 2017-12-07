#include "gtest/gtest.h"
#include "demo04.h"

/* 示例四：
 * 证实 EXPECT_XX() 方法会实际执行参数中的表达式，并可能因此产生副作用
*/

// Tests the Increment() method.
TEST(Counter, Increment) {
    Counter c;

    // EXPECT_EQ() evaluates its arguments exactly once, so they
    // can have side effects.

    EXPECT_EQ(0, c.Increment());
    EXPECT_EQ(1, c.Increment());
    EXPECT_EQ(2, c.Increment());
}
