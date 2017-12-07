#include <stdio.h>
#include "gtest/gtest.h"

/* 示例九：
 * 使用事件监听器替换测试结果的输出
 *
 * 继承 EmptyTestEventListener 类型来监听测试过程中的事件并做响应
*/

// 通过 using 语句来简化对指定命名空间中指定类型的引用
using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

namespace {

// Provides alternative output mode which produces minimal amount of
// information about tests.
class TersePrinter : public EmptyTestEventListener {
private:
    // Called before any test activity starts.
    virtual void OnTestProgramStart(const UnitTest& /* unit_test */) {}

    // Called after all test activities have ended.
    virtual void OnTestProgramEnd(const UnitTest& unit_test) {
        fprintf(stdout, "TEST %s\n", unit_test.Passed() ? "PASSED" : "FAILED");
        fflush(stdout);
    }

    // Called before a test starts.
    virtual void OnTestStart(const TestInfo& test_info) {
        fprintf(stdout,
                "*** Test %s.%s starting.\n",
                test_info.test_case_name(),
                test_info.name());
        fflush(stdout);
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(const TestPartResult& test_part_result) {
        fprintf(stdout,
                "%s in %s:%d\n%s\n",
                test_part_result.failed() ? "*** Failure" : "Success",
                test_part_result.file_name(),
                test_part_result.line_number(),
                test_part_result.summary());
        fflush(stdout);
    }

    // Called after a test ends.
    virtual void OnTestEnd(const TestInfo& test_info) {
        fprintf(stdout,
                "*** Test %s.%s ending.\n",
                test_info.test_case_name(),
                test_info.name());
        fflush(stdout);
    }
};  // class TersePrinter

TEST(CustomOutputTest, PrintsMessage) {
    printf("Printing something from the test body...\n");
}

TEST(CustomOutputTest, Succeeds) {
    SUCCEED() << "SUCCEED() has been invoked from here";
}

TEST(CustomOutputTest, Fails) {
    EXPECT_EQ(1, 2) << "This test fails in order to demonstrate alternative failure messages";
}

}  // namespace

// 自定义的main()方法会自动替换库中内置的main()方法
int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);

    // 运行时默认使用自定义的输出，加上“--origin_output”参数可恢复为默认的GTest输出
    bool terse_output = true;
    if (argc > 1 && strcmp(argv[1], "--origin_output") == 0 )
        terse_output = false;
    else
        printf("%s\n", "Run this program with --origin_output to see origin gtest messages.");

    UnitTest& unit_test = *UnitTest::GetInstance();

    // 去除标准的输出内容，替换为自定义监听器的输出
    if (terse_output) {
        TestEventListeners& listeners = unit_test.listeners();

        // Removes the default console output listener from the list so it will
        // not receive events from Google Test and won't print any output. Since
        // this operation transfers ownership of the listener to the caller we
        // have to delete it as well.
        delete listeners.Release(listeners.default_result_printer());

        // Adds the custom output listener to the list. It will now receive
        // events from Google Test and print the alternative output. We don't
        // have to worry about deleting it since Google Test assumes ownership
        // over it after adding it to the list.
        listeners.Append(new TersePrinter);
    }
    int ret_val = RUN_ALL_TESTS();

    // This is an example of using the UnitTest reflection API to inspect test
    // results. Here we discount failures from the tests we expected to fail.
    int unexpectedly_failed_tests = 0;
    for (int i = 0; i < unit_test.total_test_case_count(); ++i) {
        const TestCase& test_case = *unit_test.GetTestCase(i);
        for (int j = 0; j < test_case.total_test_count(); ++j) {
            const TestInfo& test_info = *test_case.GetTestInfo(j);
            // Counts failed tests that were not meant to fail (those without
            // 'Fails' in the name).
            if (test_info.result()->Failed() &&
                    strcmp(test_info.name(), "Fails") != 0) {
                unexpectedly_failed_tests++;
            }
        }
    }

    // Test that were meant to fail should not affect the test program outcome.
    if (unexpectedly_failed_tests == 0)
        ret_val = 0;

    return ret_val;
}
