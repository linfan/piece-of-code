/**
 * @file OutputCalculator.cc
 * @brief calculate and print the answer according to given information
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include "OutputCalculator.h"
#include "InputReader.h"
#include "RomanTranslater.h"
#include "GalaxyTranslater.h"

OutputCalculator::OutputCalculator()
{
}
OutputCalculator::~OutputCalculator()
{
}

void OutputCalculator::SetInputInfo(InputInformation* info)
{
    pQuestions = &(info->questions);
    pUnitMap = &(info->unitMap);
    pNumberMap = &(info->numberMap);

    calculateUnitValueMap();
}

void OutputCalculator::calculateUnitValueMap()
{
    for_each(pUnitMap->begin(), pUnitMap->end(),
        [this] (pair<string, Unit*> i) {
            string romanNum = GalaxyTranslater::Ins()->Translate((i.second)->nums, *pNumberMap);
            int arabicNum = RomanTranslater::Ins()->Translate(romanNum);
            unitValueMap[i.first] = (1.0 * (i.second)->value) / arabicNum;
        }
    );
}

string OutputCalculator::vectorToString(vector<string> v)
{
    string str = "";
    vector<string>::iterator i = v.begin();
    while (i != v.end())
    {
        str += (*i + string(" "));
        ++i;
    }
    return str;
}

string OutputCalculator::numberToString(int num)
{
    ostringstream convert;
    convert << num;
    return convert.str();
}

void OutputCalculator::AnswerQuestions()
{
    for_each(pQuestions->begin(), pQuestions->end(),
        [this] (Question* i) {
            string ansStr;
            if (i->valid) {
                if (i->unit == "") {
                    ansStr = answerNumberQuestion(i->nums);
                } else {
                    ansStr = answerUnitNumberQuestion(i->nums, i->unit);
                }
            } else {
                ansStr = answerInvalidQuestion();
            }
            cout << ansStr << endl;
        }
    );
}

string OutputCalculator::answerNumberQuestion(vector<string> galNums)
{
    string galaxyNum = vectorToString(galNums);
    string romanNum = GalaxyTranslater::Ins()->Translate(galNums, *pNumberMap);
    int arabicNum = RomanTranslater::Ins()->Translate(romanNum);
    return galaxyNum + string("is ") + numberToString(arabicNum);
}

string OutputCalculator::answerUnitNumberQuestion(vector<string> galNums, string unit)
{
    string galaxyNum = vectorToString(galNums);
    string romanNum = GalaxyTranslater::Ins()->Translate(galNums, *pNumberMap);
    int arabicNum = RomanTranslater::Ins()->Translate(romanNum);
    int creditValue = int(unitValueMap[unit] * arabicNum);
    return galaxyNum + unit + string(" is ") + numberToString(creditValue) + string(" Credits");
}

string OutputCalculator::answerInvalidQuestion()
{
    return "I have no idea what you are talking about";
}

