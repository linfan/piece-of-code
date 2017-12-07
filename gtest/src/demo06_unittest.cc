#include "prime_tables.h"
#include "gtest/gtest.h"

/* 示例六：
 * 基于类型的数据驱动测试
 *
 * TYPED_TEST_CASE
 * TYPED_TEST
 * TYPED_TEST_CASE_P
 * TYPED_TEST_P
 * REGISTER_TYPED_TEST_CASE_P
 * INSTANTIATE_TYPED_TEST_CASE_P
*/


// Google Test 测试框架提供两种基于类型的数据驱动测试方法
// 第一种是“泛类型测试”，当你已经知道所有需要被测试的类型时，可以使用这种方法

// 首先声明一个创建实例的模板方法（泛型），并定义它的多种具体类型实现
template <class T>
PrimeTable* CreatePrimeTable();

template <>
PrimeTable* CreatePrimeTable<OnTheFlyPrimeTable>() {
    return new OnTheFlyPrimeTable;
}

template <>
PrimeTable* CreatePrimeTable<PreCalculatedPrimeTable>() {
    return new PreCalculatedPrimeTable(10000);
}

// 然后定义一个同样使用模板类型的测试类
template <class T>
class PrimeTableTest : public testing::Test {
protected:
    // 构造函数使用模板参数生成一组测试待数据
    PrimeTableTest() : table_(CreatePrimeTable<T>()) {}

    virtual ~PrimeTableTest() {
        delete table_;
    }

    // 将参数对象定义为所有测试数据类的公共接口PrimeTable类型（纯虚类）
    PrimeTable* const table_;
};

#if GTEST_HAS_TYPED_TEST


// 然后使用 TYPED_TEST_CASE(测试类名称, 待测类型列表) 方法声明该测试类采用基于类型的测试
typedef testing::Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> Implementations; // 定义待测试的类型列表
TYPED_TEST_CASE(PrimeTableTest, Implementations);

// 接下来使用 TYPED_TEST(测试类名称, 测试用例名称) 方法定义测试用例（与 TEST_F 方法类似）
TYPED_TEST(PrimeTableTest, ReturnsFalseForNonPrimes) {
    // Inside the test body, you can refer to the type parameter by
    // TypeParam, and refer to the fixture class by TestFixture.  We
    // don't need them in this example.

    // Since we are in the template world, C++ requires explicitly
    // writing 'this->' when referring to members of the fixture class.
    // This is something you have to learn to live with.
    EXPECT_FALSE(this->table_->IsPrime(-5));
    EXPECT_FALSE(this->table_->IsPrime(0));
    EXPECT_FALSE(this->table_->IsPrime(1));
    EXPECT_FALSE(this->table_->IsPrime(4));
    EXPECT_FALSE(this->table_->IsPrime(6));
    EXPECT_FALSE(this->table_->IsPrime(100));
}

TYPED_TEST(PrimeTableTest, ReturnsTrueForPrimes) {
    EXPECT_TRUE(this->table_->IsPrime(2));
    EXPECT_TRUE(this->table_->IsPrime(3));
    EXPECT_TRUE(this->table_->IsPrime(5));
    EXPECT_TRUE(this->table_->IsPrime(7));
    EXPECT_TRUE(this->table_->IsPrime(11));
    EXPECT_TRUE(this->table_->IsPrime(131));
}

TYPED_TEST(PrimeTableTest, CanGetNextPrime) {
    EXPECT_EQ(2, this->table_->GetNextPrime(0));
    EXPECT_EQ(3, this->table_->GetNextPrime(2));
    EXPECT_EQ(5, this->table_->GetNextPrime(3));
    EXPECT_EQ(7, this->table_->GetNextPrime(5));
    EXPECT_EQ(11, this->table_->GetNextPrime(7));
    EXPECT_EQ(131, this->table_->GetNextPrime(128));
}

// 现在 Google Test 会自动将使用 TYPED_TEST 定义的用例在每一个通过 TYPED_TEST_CASE 定义的待测类实例上执行
// 这样就避免了对于许多相似类型编写大量重复的测试用例

#endif  // GTEST_HAS_TYPED_TEST

#if GTEST_HAS_TYPED_TEST_P


// 有时候，在编写测试时我们无法预知将来实现特定接口的类型会有哪些
// Google Test 测试框架的第二种基于类型的数据驱动测试方法称为“参数化类型测试”
// 它比前一种方法要稍微麻烦一点

// 首先定义一个使用模板的测试类，这里我们复用前例中的 PrimeTableTest 测试类
template <class T>
class PrimeTableTest2 : public PrimeTableTest<T> {
};

// 然后使用 TYPED_TEST_CASE_P(测试类名称) 将其声明为参数化类型测试
TYPED_TEST_CASE_P(PrimeTableTest2);

// 接下来使用 TYPED_TEST_P(测试类名称, 测试用例名称) 方法定义测试用例（与 TEST_F 方法类似）
TYPED_TEST_P(PrimeTableTest2, ReturnsFalseForNonPrimes) {
    EXPECT_FALSE(this->table_->IsPrime(-5));
    EXPECT_FALSE(this->table_->IsPrime(0));
    EXPECT_FALSE(this->table_->IsPrime(1));
    EXPECT_FALSE(this->table_->IsPrime(4));
    EXPECT_FALSE(this->table_->IsPrime(6));
    EXPECT_FALSE(this->table_->IsPrime(100));
}

TYPED_TEST_P(PrimeTableTest2, ReturnsTrueForPrimes) {
    EXPECT_TRUE(this->table_->IsPrime(2));
    EXPECT_TRUE(this->table_->IsPrime(3));
    EXPECT_TRUE(this->table_->IsPrime(5));
    EXPECT_TRUE(this->table_->IsPrime(7));
    EXPECT_TRUE(this->table_->IsPrime(11));
    EXPECT_TRUE(this->table_->IsPrime(131));
}

TYPED_TEST_P(PrimeTableTest2, CanGetNextPrime) {
    EXPECT_EQ(2, this->table_->GetNextPrime(0));
    EXPECT_EQ(3, this->table_->GetNextPrime(2));
    EXPECT_EQ(5, this->table_->GetNextPrime(3));
    EXPECT_EQ(7, this->table_->GetNextPrime(5));
    EXPECT_EQ(11, this->table_->GetNextPrime(7));
    EXPECT_EQ(131, this->table_->GetNextPrime(128));
}

// 最后需要一个额外步骤，使用 REGISTER_TYPED_TEST_CASE_P 枚举所有测试用例
REGISTER_TYPED_TEST_CASE_P(
    PrimeTableTest2,  // 第一个参数是测试类的名称
    ReturnsFalseForNonPrimes, ReturnsTrueForPrimes, CanGetNextPrime); // 余下参数是测试用例列表

// At this point the test pattern is done.  However, you don't have
// any real test yet as you haven't said which types you want to run
// the tests with.

// To turn the abstract test pattern into real tests, you instantiate
// it with a list of types.  Usually the test pattern will be defined
// in a .h file, and anyone can #include and instantiate it.  You can
// even instantiate it more than once in the same program.  To tell
// different instances apart, you give each of them a name, which will
// become part of the test case name and can be used in test filters.

// The list of types we want to test.  Note that it doesn't have to be
// defined at the time we write the TYPED_TEST_P()s.
typedef testing::Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> PrimeTableImplementations;
INSTANTIATE_TYPED_TEST_CASE_P(OnTheFlyAndPreCalculated,    // Instance name
                              PrimeTableTest2,             // Test case name
                              PrimeTableImplementations);  // Type list

#endif  // GTEST_HAS_TYPED_TEST_P
