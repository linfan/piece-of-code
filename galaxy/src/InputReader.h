/**
 * @file InputReader.h
 * @brief read input file, parse the requests and questions
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
using namespace std;

/** @class Question
 * @brief Represent a question in the queries
 */
struct Question
{
    bool valid;
    string unit;
    string secondUnit;
    vector<string> nums;
};

/** @class Unit
 * @brief Represent a Galaxy unit information
 */
struct Unit
{
    int value;
    vector<string> nums;
};

/** @class InputInformation
 * @brief Use to communicate with OutputCalculator
 * Hide the information details from end user
 */
struct InputInformation
{
    const vector<Question*>& questions;
    const map<string, string>& numberMap;
    const map<string, Unit*>& unitMap;
};

/** @class InputReader
 * @brief Use to parse input text from a file
 */
class InputReader
{
    private:
        /** Question list
         */
        vector<Question*> questions;
        /** Galaxy number and Roman number mapping
         */
        map<string, string> numberMap;
        /** Galaxy unit and it's related info mapping
         */
        map<string, Unit*> unitMap;
    protected:
        InputReader(const InputReader&);
        void parseLine(string line);
        void parseQuestion(vector<string>& pieces);
        void parseUnitInfo(vector<string>& pieces);
        void parseNumInfo(vector<string>& pieces);
        bool searchInVector(const string& str, const vector<string>& pieces,
                vector<string>::iterator& i);
    public:
        InputReader();
        virtual ~InputReader();
        /** Parse specified input text file
         */
        void ParseFile(string inputFile);
        const vector<Question*>& GetQuestionList() { return questions; }
        const map<string, string>& GetNumberMap() { return numberMap; }
        const map<string, Unit*>& GetUnitMap() { return unitMap; }
        /** Get parsed information
         */
        InputInformation* GetInputInformation()
            { return new InputInformation{ .questions = GetQuestionList(),
                .numberMap = GetNumberMap(), .unitMap = GetUnitMap() }; }
};

#endif  // _INPUT_READER_H_

