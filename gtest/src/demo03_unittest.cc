#include "demo03.h"
#include "gtest/gtest.h"

/* 示例三：
 * 使用 Test类型 和 TEST_F() 方法测试自定义类型的对象
 *
 * 测试类中的 SetUp() 和 TearDown() 方法会在每个用例执行前后自动执行
 * TEST_F() 方法的两个参数为 测试类名称 和 测试用例名称
 *          在该方法中可以访问相应测试类的protected成员
*/

// To use a test fixture, derive a class from testing::Test.
class QueueTest : public testing::Test {

protected:

    // virtual void SetUp() will be called before each test is run.
    virtual void SetUp() {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }

    // virtual void TearDown() will be called after each test is run.
    virtual void TearDown() {
    }

    // A helper function that some test uses.
    static int Double(int n) {
        return 2 * n;
    }

    // A helper function for testing Queue::Map().
    void MapTester(const Queue<int> * q) {
        // 创建一个每个元素值恰好等于源队列相应值一倍的新队列
        const Queue<int> * const new_q = q->Map(Double);

        // 验证新队列的长度与源队列相同
        ASSERT_EQ(q->Size(), new_q->Size());

        // 验证新队列中的元素值是源队列相应元素值的一倍
        for ( const QueueNode<int> * n1 = q->Head(), * n2 = new_q->Head();
                n1 != NULL; n1 = n1->next(), n2 = n2->next() ) {
            EXPECT_EQ(2 * n1->element(), n2->element());
        }

        delete new_q;
    }

    // 声明在测试中会使用到的成员变量
    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};

// When you have a test fixture, you define a test using TEST_F instead of TEST.

// Tests the default c'tor.
TEST_F(QueueTest, DefaultConstructor) {
    // You can access data in the test fixture here.
    EXPECT_EQ(0u, q0_.Size());
}

// Tests Dequeue().
TEST_F(QueueTest, Dequeue) {
    int * n = q0_.Dequeue();
    EXPECT_TRUE(n == NULL);

    n = q1_.Dequeue();
    ASSERT_TRUE(n != NULL);
    EXPECT_EQ(1, *n);
    EXPECT_EQ(0u, q1_.Size());
    delete n;

    n = q2_.Dequeue();
    ASSERT_TRUE(n != NULL);
    EXPECT_EQ(2, *n);
    EXPECT_EQ(1u, q2_.Size());
    delete n;
}

// Tests the Queue::Map() function.
TEST_F(QueueTest, Map) {
    MapTester(&q0_);
    MapTester(&q1_);
    MapTester(&q2_);
}
