/**
 * @file test_GalaxyTranslater.cc
 * @brief unittest for GalaxyTranslater class
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include <gtest/gtest.h>
#include "GalaxyTranslater.h"

class GalaxyTranslaterTest : public testing::Test
{
    protected:
        map<string, string> goodDict;
        map<string, string> badDict;

        virtual void SetUp()
        {
            goodDict["iihhgg"] = "I";
            goodDict["vvttss"] = "V";
            goodDict["xxyyzz"] = "X";
            goodDict["llkkjj"] = "L";
            goodDict["ccbbaa"] = "C";
            goodDict["ddeeff"] = "D";
            goodDict["mmnnoo"] = "M";

            badDict["iihhgg"] = "I";
            badDict["vvttss"] = ""; // empty
            badDict["xxyyzz"] = "X";
            badDict["llkkjj"] = "L";
        }
        virtual void TearDown()
        {
        }
};

TEST_F(GalaxyTranslaterTest, TranslateValidNumber)
{
    vector<string> galaxyNum;
    galaxyNum.push_back("mmnnoo");
    galaxyNum.push_back("ddeeff");
    galaxyNum.push_back("ccbbaa");
    galaxyNum.push_back("ccbbaa");
    galaxyNum.push_back("iihhgg");
    galaxyNum.push_back("vvttss");
    EXPECT_EQ("MDCCIV", GalaxyTranslater::Ins()->Translate(galaxyNum, goodDict));
}

TEST_F(GalaxyTranslaterTest, TranslateInvalidNumber)
{
    vector<string> galaxyNum;
    galaxyNum.push_back("mmnnoo");
    galaxyNum.push_back("eeffgg");
    galaxyNum.push_back("llkkjj");
    EXPECT_THROW(GalaxyTranslater::Ins()->Translate(galaxyNum, goodDict),
            InvalidGalaxyNumberException);
}

TEST_F(GalaxyTranslaterTest, TranslateUsingBadDictionary)
{
    vector<string> galaxyNum;
    galaxyNum.push_back("llkkjj");
    galaxyNum.push_back("xxyyzz");
    galaxyNum.push_back("vvttss");
    EXPECT_THROW(GalaxyTranslater::Ins()->Translate(galaxyNum, badDict),
            InvalidGalaxyNumberException);
}

