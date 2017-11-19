/**
 * @file test_RomanTranslater.cc
 * @brief unittest for RomanTranslater class
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <gtest/gtest.h>
#include "RomanTranslater.h"
using namespace std;

struct RomanAndArabic
{
    int arabic;
    string roman;
};

class RomanTranslaterTest : public testing::Test
{
    protected:
        list<RomanAndArabic*> positive_cases;
        list<RomanAndArabic*> negative_cases;

        virtual void SetUp()
        {
            positive_cases.push_back( new RomanAndArabic { 1, "I" } );
            positive_cases.push_back( new RomanAndArabic { 2, "II" } );
            positive_cases.push_back( new RomanAndArabic { 3, "III" } );
            positive_cases.push_back( new RomanAndArabic { 4, "IV" } );
            positive_cases.push_back( new RomanAndArabic { 5, "V" } );
            positive_cases.push_back( new RomanAndArabic { 6, "VI" } );
            positive_cases.push_back( new RomanAndArabic { 7, "VII" } );
            positive_cases.push_back( new RomanAndArabic { 8, "VIII" } );
            positive_cases.push_back( new RomanAndArabic { 9, "IX" } );
            positive_cases.push_back( new RomanAndArabic { 10, "X" } );
            positive_cases.push_back( new RomanAndArabic { 50, "L" } );
            positive_cases.push_back( new RomanAndArabic { 100, "C" } );
            positive_cases.push_back( new RomanAndArabic { 500, "D" } );
            positive_cases.push_back( new RomanAndArabic { 1000, "M" } );
            positive_cases.push_back( new RomanAndArabic { 31, "XXXI" } );
            positive_cases.push_back( new RomanAndArabic { 148, "CXLVIII" } );
            positive_cases.push_back( new RomanAndArabic { 294, "CCXCIV" } );
            positive_cases.push_back( new RomanAndArabic { 312, "CCCXII" } );
            positive_cases.push_back( new RomanAndArabic { 421, "CDXXI" } );
            positive_cases.push_back( new RomanAndArabic { 528, "DXXVIII" } );
            positive_cases.push_back( new RomanAndArabic { 621, "DCXXI" } );
            positive_cases.push_back( new RomanAndArabic { 782, "DCCLXXXII" } );
            positive_cases.push_back( new RomanAndArabic { 870, "DCCCLXX" } );
            positive_cases.push_back( new RomanAndArabic { 941, "CMXLI" } );
            positive_cases.push_back( new RomanAndArabic { 1043, "MXLIII" } );
            positive_cases.push_back( new RomanAndArabic { 1110, "MCX" } );
            positive_cases.push_back( new RomanAndArabic { 1226, "MCCXXVI" } );
            positive_cases.push_back( new RomanAndArabic { 1301, "MCCCI" } );
            positive_cases.push_back( new RomanAndArabic { 1485, "MCDLXXXV" } );
            positive_cases.push_back( new RomanAndArabic { 1509, "MDIX" } );
            positive_cases.push_back( new RomanAndArabic { 1607, "MDCVII" } );
            positive_cases.push_back( new RomanAndArabic { 1754, "MDCCLIV" } );
            positive_cases.push_back( new RomanAndArabic { 1832, "MDCCCXXXII" } );
            positive_cases.push_back( new RomanAndArabic { 1993, "MCMXCIII" } );
            positive_cases.push_back( new RomanAndArabic { 2074, "MMLXXIV" } );
            positive_cases.push_back( new RomanAndArabic { 2152, "MMCLII" } );
            positive_cases.push_back( new RomanAndArabic { 2212, "MMCCXII" } );
            positive_cases.push_back( new RomanAndArabic { 2343, "MMCCCXLIII" } );
            positive_cases.push_back( new RomanAndArabic { 2499, "MMCDXCIX" } );
            positive_cases.push_back( new RomanAndArabic { 2574, "MMDLXXIV" } );
            positive_cases.push_back( new RomanAndArabic { 2646, "MMDCXLVI" } );
            positive_cases.push_back( new RomanAndArabic { 2723, "MMDCCXXIII" } );
            positive_cases.push_back( new RomanAndArabic { 2892, "MMDCCCXCII" } );
            positive_cases.push_back( new RomanAndArabic { 2975, "MMCMLXXV" } );
            positive_cases.push_back( new RomanAndArabic { 3051, "MMMLI" } );
            positive_cases.push_back( new RomanAndArabic { 3185, "MMMCLXXXV" } );
            positive_cases.push_back( new RomanAndArabic { 3250, "MMMCCL" } );
            positive_cases.push_back( new RomanAndArabic { 3313, "MMMCCCXIII" } );
            positive_cases.push_back( new RomanAndArabic { 3408, "MMMCDVIII" } );
            positive_cases.push_back( new RomanAndArabic { 3501, "MMMDI" } );
            positive_cases.push_back( new RomanAndArabic { 3610, "MMMDCX" } );
            positive_cases.push_back( new RomanAndArabic { 3743, "MMMDCCXLIII" } );
            positive_cases.push_back( new RomanAndArabic { 3844, "MMMDCCCXLIV" } );
            positive_cases.push_back( new RomanAndArabic { 3888, "MMMDCCCLXXXVIII" } );
            positive_cases.push_back( new RomanAndArabic { 3940, "MMMCMXL" } );
            positive_cases.push_back( new RomanAndArabic { 3999, "MMMCMXCIX" } );

            negative_cases.push_back( new RomanAndArabic { -1, "MMMM" } );
            negative_cases.push_back( new RomanAndArabic { -1, "DD" } );
            negative_cases.push_back( new RomanAndArabic { -1, "CCCC" } );
            negative_cases.push_back( new RomanAndArabic { -1, "LL" } );
            negative_cases.push_back( new RomanAndArabic { -1, "XXXX" } );
            negative_cases.push_back( new RomanAndArabic { -1, "VV" } );
            negative_cases.push_back( new RomanAndArabic { -1, "IIII" } );
            negative_cases.push_back( new RomanAndArabic { -1, "TT" } );
            negative_cases.push_back( new RomanAndArabic { -1, "MMBB" } );
            negative_cases.push_back( new RomanAndArabic { -1, "" } );

        }

        virtual void TearDown()
        {
            for_each(positive_cases.begin(), positive_cases.end(),
                [] (RomanAndArabic* i) {
                    delete i;
                }
            );
            positive_cases.clear();
            for_each(negative_cases.begin(), negative_cases.end(),
                [] (RomanAndArabic* i) {
                    delete i;
                }
            );
            negative_cases.clear();
        }
};

TEST_F(RomanTranslaterTest, TranslateValidNumber)
{
    for_each(positive_cases.begin(), positive_cases.end(),
            [] (RomanAndArabic* i) {
                EXPECT_EQ(i->arabic, RomanTranslater::Ins()->Translate(i->roman))
                    << "Roman: " << i->roman << " <-> Arabic: " << i->arabic;
            }
        );
}

TEST_F(RomanTranslaterTest, TranslateInvalidNumber)
{
    for_each(negative_cases.begin(), negative_cases.end(),
            [] (RomanAndArabic* i) {
                EXPECT_THROW(RomanTranslater::Ins()->Translate(i->roman), InvalidRomanNumberException)
                    << "Roman: " << i->roman << " <=> Arabic: " << i->arabic;
            }
        );
}

