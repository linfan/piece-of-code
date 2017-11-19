/**
 * @file OutputCalculator.h
 * @brief calculate and print the answer according to given information
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#ifndef _OUTPUT_CALCULATOR_H_
#define _OUTPUT_CALCULATOR_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../unittest/include/gtest/gtest_prod.h" // unittest support
using namespace std;

class InputInformation;
class Question;
class Unit;

/** @class OutputCalculator
 * @brief Result writer , it answer the requested questions
 */
class OutputCalculator
{
    private:
        /** Same structures as InputReader has
         */
        const vector<Question*>* pQuestions;
        const map<string, string>* pNumberMap;
        const map<string, Unit*>* pUnitMap;
        /** A unit name to value that it worth mapping
         */
        map<string, float> unitValueMap;
        // Allow below unittest case to access private memebers
        FRIEND_TEST(OutputCalculatorTest, testAnswerNumberQuestion);
        FRIEND_TEST(OutputCalculatorTest, testAnswerUnitNumberQuestion);
        FRIEND_TEST(OutputCalculatorTest, testAnswerInvalidQuestion);
    protected:
        OutputCalculator(const OutputCalculator&);
        /** Calculate the unitValueMap
         */
        void calculateUnitValueMap();
        string vectorToString(vector<string> v);
        string numberToString(int num);
        string answerNumberQuestion(vector<string> galNums);
        string answerUnitNumberQuestion(vector<string> galNums, string unit);
        string answerInvalidQuestion();
    public:
        OutputCalculator();
        virtual ~OutputCalculator();
        /** Get all parsed input information from a InputInformation structure
         */
        void SetInputInfo(InputInformation* info);
        /** If there are question in the input queries, answer them
         */
        void AnswerQuestions();
};

#endif  // _OUTPUT_CALCULATOR_H_

