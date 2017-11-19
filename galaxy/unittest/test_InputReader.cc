/**
 * @file test_InputReader.cc
 * @brief unittest for InputReader class
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include <gtest/gtest.h>
#include "InputReader.h"

class InputReaderTest: public testing::Test
{
    protected:
        InputReader reader;

        virtual void SetUp()
        {
            reader.ParseFile("../unittest/input.txt");
        }
        virtual void TearDown()
        {
        }
};

TEST_F(InputReaderTest, testParseQuestion)
{
    const vector<Question*>& ques = reader.GetQuestionList();
    vector<Question*>::const_iterator iter = ques.begin();

    EXPECT_TRUE((*iter)->valid);
    EXPECT_EQ("", (*iter)->unit);
    EXPECT_EQ("pish", (*iter)->nums[0]);
    EXPECT_EQ("tegj", (*iter)->nums[1]);
    EXPECT_EQ("glob", (*iter)->nums[2]);
    EXPECT_EQ("glob", (*iter)->nums[3]);

    ++iter;
    EXPECT_TRUE((*iter)->valid);
    EXPECT_EQ("Gold", (*iter)->unit);
    EXPECT_EQ("glob", (*iter)->nums[0]);
    EXPECT_EQ("prok", (*iter)->nums[1]);

    ++iter;
    EXPECT_FALSE((*iter)->valid);
}

TEST_F(InputReaderTest, testParseUnitInfo)
{
    const map<string, Unit*>& unitMap = reader.GetUnitMap();

    const Unit* unitInfo = unitMap.at("Gold");
    EXPECT_EQ(57800, unitInfo->value);
    EXPECT_EQ("glob", unitInfo->nums[0]);
    EXPECT_EQ("prok", unitInfo->nums[1]);
}

TEST_F(InputReaderTest, testParseNumsInfo)
{
    const map<string, string>& numMap = reader.GetNumberMap();

    EXPECT_EQ("I", numMap.at("glob"));
    EXPECT_EQ("V", numMap.at("prok"));
    EXPECT_EQ("X", numMap.at("pish"));
    EXPECT_EQ("L", numMap.at("tegj"));
}

