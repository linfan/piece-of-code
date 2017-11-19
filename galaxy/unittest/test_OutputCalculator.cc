/**
 * @file test_OutputCalculator.cc
 * @brief unittest for OutputCalculator class
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include <gtest/gtest.h>
#include "OutputCalculator.h"

class OutputCalculatorTest: public testing::Test
{
    protected:
        OutputCalculator calc;
        map<string, string> dict;
        map<string, float> unitVal;

        virtual void SetUp()
        {
            dict["iihhgg"] = "I";
            dict["vvttss"] = "V";
            dict["xxyyzz"] = "X";
            dict["llkkjj"] = "L";
            dict["ccbbaa"] = "C";
            dict["ddeeff"] = "D";
            dict["mmnnoo"] = "M";
            
            unitVal["Gold"] = 3;
            unitVal["Silver"] = 2;
        }
        virtual void TearDown()
        {
        }
};

TEST_F(OutputCalculatorTest, testAnswerNumberQuestion)
{
    calc.pNumberMap = &dict;
    vector<string> galaxyNums;
    galaxyNums.push_back("mmnnoo");
    galaxyNums.push_back("xxyyzz");
    galaxyNums.push_back("vvttss");
    EXPECT_EQ("mmnnoo xxyyzz vvttss is 1015", 
        calc.answerNumberQuestion(galaxyNums));
}

TEST_F(OutputCalculatorTest, testAnswerUnitNumberQuestion)
{
    calc.pNumberMap = &dict;
    calc.unitValueMap = unitVal;
    vector<string> galaxyNums;
    galaxyNums.push_back("mmnnoo");
    galaxyNums.push_back("xxyyzz");
    galaxyNums.push_back("vvttss");
    EXPECT_EQ("mmnnoo xxyyzz vvttss Gold is 3045 Credits", 
        calc.answerUnitNumberQuestion(galaxyNums, "Gold"));
}

TEST_F(OutputCalculatorTest, testAnswerInvalidQuestion)
{
    EXPECT_EQ("I have no idea what you are talking about", 
        calc.answerInvalidQuestion());
}

