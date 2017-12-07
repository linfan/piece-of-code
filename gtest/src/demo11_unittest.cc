#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "demo11.h"

#if GTEST_OS_WINDOWS
// MSDN says the header file to be included for STDMETHOD is BaseTyps.h but
// we are getting compiler errors if we use basetyps.h, hence including
// objbase.h for definition of STDMETHOD.
# include <objbase.h>
#endif  // GTEST_OS_WINDOWS

/* 示例十一：
 * 使用GMock创建测试桩
 *
 * GTEST_DISALLOW_COPY_AND_ASSIGN_
 * MOCK_METHOD
 * MOCK_CONST_METHOD
 * EXPECT_CALL
 * MockFunction 类型
*/


namespace testing {

using std::string;
using testing::_;
using testing::A;
using testing::An;
using testing::AnyNumber;
using testing::Const;
using testing::DoDefault;
using testing::Eq;
using testing::Lt;
using testing::MockFunction;
using testing::Ref;
using testing::Return;
using testing::ReturnRef;
using testing::TypedEq;

// Const qualifiers on arguments were once (incorrectly) considered
// significant in determining whether two virtual functions had the same
// signature. This was fixed in Visual Studio 2008. However, the compiler
// still emits a warning that alerts about this change in behavior.
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable : 4373)
#endif

// 1. 实现一个接口的测试桩
class MockFoo : public FooInterface {
public:
    MockFoo() {}

    // Makes sure that a mock function parameter can be named.
    MOCK_METHOD1(VoidReturning, void(int n));

    // Makes sure that a mock function parameter can be unnamed.
    MOCK_METHOD0(Nullary, int());
    MOCK_METHOD1(Unary, bool(int));
    MOCK_METHOD2(Binary, long(short, int));
    MOCK_METHOD10(Decimal, int(bool, char, short, int, long, float,
                               double, unsigned, char*, const string& str));

    MOCK_METHOD1(TakesNonConstReference, bool(int&));
    MOCK_METHOD1(TakesConstReference, string(const int&));
    MOCK_METHOD1(TakesConst, bool(const int));

    MOCK_METHOD0(OverloadedOnArgumentNumber, int());
    MOCK_METHOD1(OverloadedOnArgumentNumber, int(int));

    MOCK_METHOD1(OverloadedOnArgumentType, int(int));
    MOCK_METHOD1(OverloadedOnArgumentType, char(char));

    MOCK_METHOD0(OverloadedOnConstness, int());
    MOCK_CONST_METHOD0(OverloadedOnConstness, char());

    MOCK_METHOD1(TypeWithHole, int(int (*)()));
    MOCK_METHOD1(TypeWithComma, int(const std::map<int, string>&));

    // Tests that the function return type can contain unprotected comma.
    MOCK_METHOD0(ReturnTypeWithComma, std::map<int, string>());
    MOCK_CONST_METHOD1(ReturnTypeWithComma, std::map<int, string>(int));

#if GTEST_OS_WINDOWS
    MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, CTNullary, int());
    MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CTUnary, bool(int));
    MOCK_METHOD10_WITH_CALLTYPE(STDMETHODCALLTYPE, CTDecimal, int(bool b, char c,
                                short d, int e, long f, float g, double h, unsigned i, char* j,
                                const string& k));
    MOCK_CONST_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CTConst, char(int));

    // Tests that the function return type can contain unprotected comma.
    MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, CTReturnTypeWithComma,
                               std::map<int, string>());
#endif  // GTEST_OS_WINDOWS

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockFoo);
};
#ifdef _MSC_VER
# pragma warning(pop)
#endif

class FunctionMockerTest : public testing::Test {
protected:
    FunctionMockerTest() : foo_(&mock_foo_) {}

    FooInterface* const foo_;
    MockFoo mock_foo_;
};

// Tests mocking a void-returning function.
TEST_F(FunctionMockerTest, MocksVoidFunction) {
    EXPECT_CALL(mock_foo_, VoidReturning(Lt(100)));
    foo_->VoidReturning(0);
}

// Tests mocking a nullary function.
TEST_F(FunctionMockerTest, MocksNullaryFunction) {
    EXPECT_CALL(mock_foo_, Nullary())
    .WillOnce(DoDefault())
    .WillOnce(Return(1));

    EXPECT_EQ(0, foo_->Nullary());
    EXPECT_EQ(1, foo_->Nullary());
}

// Tests mocking a unary function.
TEST_F(FunctionMockerTest, MocksUnaryFunction) {
    EXPECT_CALL(mock_foo_, Unary(Eq(2)))
    .Times(2)
    .WillOnce(Return(true));

    EXPECT_TRUE(foo_->Unary(2));
    EXPECT_FALSE(foo_->Unary(2));
}

// Tests mocking a binary function.
TEST_F(FunctionMockerTest, MocksBinaryFunction) {
    EXPECT_CALL(mock_foo_, Binary(2, _))
    .WillOnce(Return(3));

    EXPECT_EQ(3, foo_->Binary(2, 1));
}

// Tests mocking a decimal function.
TEST_F(FunctionMockerTest, MocksDecimalFunction) {
    EXPECT_CALL(mock_foo_, Decimal(true, 'a', 0, 0, 1L, A<float>(),
                                   Lt(100), 5U, NULL, "hi"))
    .WillOnce(Return(5));

    EXPECT_EQ(5, foo_->Decimal(true, 'a', 0, 0, 1, 0, 0, 5, NULL, "hi"));
}

// Tests mocking a function that takes a non-const reference.
TEST_F(FunctionMockerTest, MocksFunctionWithNonConstReferenceArgument) {
    int a = 0;
    EXPECT_CALL(mock_foo_, TakesNonConstReference(Ref(a)))
    .WillOnce(Return(true));

    EXPECT_TRUE(foo_->TakesNonConstReference(a));
}

// Tests mocking a function that takes a const reference.
TEST_F(FunctionMockerTest, MocksFunctionWithConstReferenceArgument) {
    int a = 0;
    EXPECT_CALL(mock_foo_, TakesConstReference(Ref(a)))
    .WillOnce(Return("Hello"));

    EXPECT_EQ("Hello", foo_->TakesConstReference(a));
}

// Tests mocking a function that takes a const variable.
TEST_F(FunctionMockerTest, MocksFunctionWithConstArgument) {
    EXPECT_CALL(mock_foo_, TakesConst(Lt(10)))
    .WillOnce(DoDefault());

    EXPECT_FALSE(foo_->TakesConst(5));
}

// Tests mocking functions overloaded on the number of arguments.
TEST_F(FunctionMockerTest, MocksFunctionsOverloadedOnArgumentNumber) {
    EXPECT_CALL(mock_foo_, OverloadedOnArgumentNumber())
    .WillOnce(Return(1));
    EXPECT_CALL(mock_foo_, OverloadedOnArgumentNumber(_))
    .WillOnce(Return(2));

    EXPECT_EQ(2, foo_->OverloadedOnArgumentNumber(1));
    EXPECT_EQ(1, foo_->OverloadedOnArgumentNumber());
}

// Tests mocking functions overloaded on the types of argument.
TEST_F(FunctionMockerTest, MocksFunctionsOverloadedOnArgumentType) {
    EXPECT_CALL(mock_foo_, OverloadedOnArgumentType(An<int>()))
    .WillOnce(Return(1));
    EXPECT_CALL(mock_foo_, OverloadedOnArgumentType(TypedEq<char>('a')))
    .WillOnce(Return('b'));

    EXPECT_EQ(1, foo_->OverloadedOnArgumentType(0));
    EXPECT_EQ('b', foo_->OverloadedOnArgumentType('a'));
}

// Tests mocking functions overloaded on the const-ness of this object.
TEST_F(FunctionMockerTest, MocksFunctionsOverloadedOnConstnessOfThis) {
    EXPECT_CALL(mock_foo_, OverloadedOnConstness());
    EXPECT_CALL(Const(mock_foo_), OverloadedOnConstness())
    .WillOnce(Return('a'));

    EXPECT_EQ(0, foo_->OverloadedOnConstness());
    EXPECT_EQ('a', Const(*foo_).OverloadedOnConstness());
}

TEST_F(FunctionMockerTest, MocksReturnTypeWithComma) {
    const std::map<int, string> a_map;
    EXPECT_CALL(mock_foo_, ReturnTypeWithComma())
    .WillOnce(Return(a_map));
    EXPECT_CALL(mock_foo_, ReturnTypeWithComma(42))
    .WillOnce(Return(a_map));

    EXPECT_EQ(a_map, mock_foo_.ReturnTypeWithComma());
    EXPECT_EQ(a_map, mock_foo_.ReturnTypeWithComma(42));
}

#if GTEST_OS_WINDOWS
// Tests mocking a nullary function with calltype.
TEST_F(FunctionMockerTest, MocksNullaryFunctionWithCallType) {
    EXPECT_CALL(mock_foo_, CTNullary())
    .WillOnce(Return(-1))
    .WillOnce(Return(0));

    EXPECT_EQ(-1, foo_->CTNullary());
    EXPECT_EQ(0, foo_->CTNullary());
}

// Tests mocking a unary function with calltype.
TEST_F(FunctionMockerTest, MocksUnaryFunctionWithCallType) {
    EXPECT_CALL(mock_foo_, CTUnary(Eq(2)))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    EXPECT_TRUE(foo_->CTUnary(2));
    EXPECT_FALSE(foo_->CTUnary(2));
}

// Tests mocking a decimal function with calltype.
TEST_F(FunctionMockerTest, MocksDecimalFunctionWithCallType) {
    EXPECT_CALL(mock_foo_, CTDecimal(true, 'a', 0, 0, 1L, A<float>(),
                                     Lt(100), 5U, NULL, "hi"))
    .WillOnce(Return(10));

    EXPECT_EQ(10, foo_->CTDecimal(true, 'a', 0, 0, 1, 0, 0, 5, NULL, "hi"));
}

// Tests mocking functions overloaded on the const-ness of this object.
TEST_F(FunctionMockerTest, MocksFunctionsConstFunctionWithCallType) {
    EXPECT_CALL(Const(mock_foo_), CTConst(_))
    .WillOnce(Return('a'));

    EXPECT_EQ('a', Const(*foo_).CTConst(0));
}

TEST_F(FunctionMockerTest, MocksReturnTypeWithCommaAndCallType) {
    const std::map<int, string> a_map;
    EXPECT_CALL(mock_foo_, CTReturnTypeWithComma())
    .WillOnce(Return(a_map));

    EXPECT_EQ(a_map, mock_foo_.CTReturnTypeWithComma());
}

#endif  // GTEST_OS_WINDOWS

// 2. 没有添加 EXPECT_CALL 行为的mock方法也可以不限次数的直接调用
class MockB {
public:
    MockB() {}
    MOCK_METHOD0(DoB, void());
private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockB);
};

TEST(ExpectCallTest, UnmentionedFunctionCanBeCalledAnyNumberOfTimes) {
    {
        MockB b;
    }

    {
        MockB b;
        b.DoB();
    }

    {
        MockB b;
        b.DoB();
        b.DoB();
    }
}

// 3. 为模板接口创建测试桩
template <typename T>
class MockStack : public StackInterface<T> {
public:
    MockStack() {}

    MOCK_METHOD1_T(Push, void(const T& elem));
    MOCK_METHOD0_T(Pop, void());
    MOCK_CONST_METHOD0_T(GetSize, int());
    MOCK_CONST_METHOD0_T(GetTop, const T& ());

    // Tests that the function return type can contain unprotected comma.
    MOCK_METHOD0_T(ReturnTypeWithComma, std::map<int, int>());
    MOCK_CONST_METHOD1_T(ReturnTypeWithComma, std::map<int, int>(int));

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockStack);
};

// Tests that template mock works.
TEST(TemplateMockTest, Works) {
    MockStack<int> mock;

    EXPECT_CALL(mock, GetSize())
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0));
    EXPECT_CALL(mock, Push(_));
    int n = 5;
    EXPECT_CALL(mock, GetTop())
    .WillOnce(ReturnRef(n));
    EXPECT_CALL(mock, Pop())
    .Times(AnyNumber());

    EXPECT_EQ(0, mock.GetSize());
    mock.Push(5);
    EXPECT_EQ(1, mock.GetSize());
    EXPECT_EQ(5, mock.GetTop());
    mock.Pop();
    EXPECT_EQ(0, mock.GetSize());
}

TEST(TemplateMockTest, MethodWithCommaInReturnTypeWorks) {
    MockStack<int> mock;

    const std::map<int, int> a_map;
    EXPECT_CALL(mock, ReturnTypeWithComma())
    .WillOnce(Return(a_map));
    EXPECT_CALL(mock, ReturnTypeWithComma(1))
    .WillOnce(Return(a_map));

    EXPECT_EQ(a_map, mock.ReturnTypeWithComma());
    EXPECT_EQ(a_map, mock.ReturnTypeWithComma(1));
}

#if GTEST_OS_WINDOWS
// Tests mocking template interfaces with calltype.

template <typename T>
class MockStackWithCallType : public StackInterfaceWithCallType<T> {
public:
    MockStackWithCallType() {}

    MOCK_METHOD1_T_WITH_CALLTYPE(STDMETHODCALLTYPE, Push, void(const T& elem));
    MOCK_METHOD0_T_WITH_CALLTYPE(STDMETHODCALLTYPE, Pop, void());
    MOCK_CONST_METHOD0_T_WITH_CALLTYPE(STDMETHODCALLTYPE, GetSize, int());
    MOCK_CONST_METHOD0_T_WITH_CALLTYPE(STDMETHODCALLTYPE, GetTop, const T & ());

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockStackWithCallType);
};

// Tests that template mock with calltype works.
TEST(TemplateMockTestWithCallType, Works) {
    MockStackWithCallType<int> mock;

    EXPECT_CALL(mock, GetSize())
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0));
    EXPECT_CALL(mock, Push(_));
    int n = 5;
    EXPECT_CALL(mock, GetTop())
    .WillOnce(ReturnRef(n));
    EXPECT_CALL(mock, Pop())
    .Times(AnyNumber());

    EXPECT_EQ(0, mock.GetSize());
    mock.Push(5);
    EXPECT_EQ(1, mock.GetSize());
    EXPECT_EQ(5, mock.GetTop());
    mock.Pop();
    EXPECT_EQ(0, mock.GetSize());
}
#endif  // GTEST_OS_WINDOWS


// 4. 基于参数重载mock方法
#define MY_MOCK_METHODS1_ \
    MOCK_METHOD0(Overloaded, void()); \
    MOCK_CONST_METHOD1(Overloaded, int(int n)); \
    MOCK_METHOD2(Overloaded, bool(bool f, int n))

class MockOverloadedOnArgNumber {
public:
    MockOverloadedOnArgNumber() {}

    MY_MOCK_METHODS1_;

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockOverloadedOnArgNumber);
};

TEST(OverloadedMockMethodTest, CanOverloadOnArgNumberInMacroBody) {
    MockOverloadedOnArgNumber mock;
    EXPECT_CALL(mock, Overloaded());
    EXPECT_CALL(mock, Overloaded(1)).WillOnce(Return(2));
    EXPECT_CALL(mock, Overloaded(true, 1)).WillOnce(Return(true));

    mock.Overloaded();
    EXPECT_EQ(2, mock.Overloaded(1));
    EXPECT_TRUE(mock.Overloaded(true, 1));
}

// 5. 基于调用者是否是常量指针重载mock方法
#define MY_MOCK_METHODS2_ \
    MOCK_CONST_METHOD1(Overloaded, int(int n)); \
    MOCK_METHOD1(Overloaded, int(int n));

class MockOverloadedOnConstness {
public:
    MockOverloadedOnConstness() {}

    MY_MOCK_METHODS2_;

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockOverloadedOnConstness);
};

TEST(OverloadedMockMethodTest, CanOverloadOnConstnessInMacroBody) {
    MockOverloadedOnConstness mock;
    const MockOverloadedOnConstness* const_mock = &mock;
    EXPECT_CALL(mock, Overloaded(1)).WillOnce(Return(2));
    EXPECT_CALL(*const_mock, Overloaded(1)).WillOnce(Return(3));

    EXPECT_EQ(2, mock.Overloaded(1));
    EXPECT_EQ(3, const_mock->Overloaded(1));
}

// 6. 直接使用 MockFunction 对象
TEST(MockFunctionTest, WorksForVoidNullary) {
    MockFunction<void()> foo;
    EXPECT_CALL(foo, Call());
    foo.Call();
}

TEST(MockFunctionTest, WorksForNonVoidNullary) {
    MockFunction<int()> foo;
    EXPECT_CALL(foo, Call())
    .WillOnce(Return(1))
    .WillOnce(Return(2));
    EXPECT_EQ(1, foo.Call());
    EXPECT_EQ(2, foo.Call());
}

TEST(MockFunctionTest, WorksForVoidUnary) {
    MockFunction<void(int)> foo;
    EXPECT_CALL(foo, Call(1));
    foo.Call(1);
}

TEST(MockFunctionTest, WorksForNonVoidBinary) {
    MockFunction<int(bool, int)> foo;
    EXPECT_CALL(foo, Call(false, 42))
    .WillOnce(Return(1))
    .WillOnce(Return(2));
    EXPECT_CALL(foo, Call(true, Ge(100)))
    .WillOnce(Return(3));
    EXPECT_EQ(1, foo.Call(false, 42));
    EXPECT_EQ(2, foo.Call(false, 42));
    EXPECT_EQ(3, foo.Call(true, 120));
}

TEST(MockFunctionTest, WorksFor10Arguments) {
    MockFunction<int(bool a0, char a1, int a2, int a3, int a4,
                     int a5, int a6, char a7, int a8, bool a9)> foo;
    EXPECT_CALL(foo, Call(_, 'a', _, _, _, _, _, _, _, _))
    .WillOnce(Return(1))
    .WillOnce(Return(2));
    EXPECT_EQ(1, foo.Call(false, 'a', 0, 0, 0, 0, 0, 'b', 0, true));
    EXPECT_EQ(2, foo.Call(true, 'a', 0, 0, 0, 0, 0, 'b', 1, false));
}

#if GTEST_HAS_STD_FUNCTION_
TEST(MockFunctionTest, AsStdFunction) {
    MockFunction<int(int)> foo;
    auto call = [](const std::function<int(int)> &f, int i) {
        return f(i);
    };
    EXPECT_CALL(foo, Call(1)).WillOnce(Return(-1));
    EXPECT_CALL(foo, Call(2)).WillOnce(Return(-2));
    EXPECT_EQ(-1, call(foo.AsStdFunction(), 1));
    EXPECT_EQ(-2, call(foo.AsStdFunction(), 2));
}

TEST(MockFunctionTest, AsStdFunctionReturnsReference) {
    MockFunction<int&()> foo;
    int value = 1;
    EXPECT_CALL(foo, Call()).WillOnce(ReturnRef(value));
    int& ref = foo.AsStdFunction()();
    EXPECT_EQ(1, ref);
    value = 2;
    EXPECT_EQ(2, ref);
}
#endif  // GTEST_HAS_STD_FUNCTION_

}  // namespace testing
