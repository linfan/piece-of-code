/**
 * @file InputReader.cc
 * @brief read input file, parse the requests and questions
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include "InputReader.h"

InputReader::InputReader()
{
}

InputReader::~InputReader()
{
    if (questions.size() > 0)
    {
        for_each(questions.begin(), questions.end(),
            [] (Question* i) {
                delete i;
            }
        );
        questions.clear();
    }
    if (unitMap.size() > 0)
    {
        for_each(unitMap.begin(), unitMap.end(),
            [] (pair<string, Unit*> i) {
                delete i.second;
            }
        );
        questions.clear();
    }
}

void InputReader::ParseFile(string inputFile)
{
    ifstream ifs;
    ifs.open(inputFile.c_str());
    string line;
    while(!ifs.eof() && ifs.good())
    {
        getline(ifs, line);
        parseLine(line);
    }
    ifs.close();
}

void InputReader::parseLine(string line)
{
    if (line == "")
        return;

    vector<string> pieces;
    istringstream sIn(line);
    istream_iterator<string> iterIn(sIn);
    istream_iterator<string> iterEnd;
    while(iterIn != iterEnd)
    {
        pieces.push_back(*iterIn);
        ++iterIn;
    }

    if (pieces[pieces.size() - 1] == "?")
    {
        parseQuestion(pieces);
    }
    else if (pieces[pieces.size() - 1] == "Credits")
    {
        parseUnitInfo(pieces);
    }
    else if (pieces[1] == "is")
    {
        parseNumInfo(pieces);
    }
}

void InputReader::parseQuestion(vector<string>& pieces)
{
    Question *question = new Question;
    question->valid = true;
    pieces.pop_back(); // remove the question mark
    vector<string>::iterator iter = pieces.begin();
    if (searchInVector("Credits", pieces, iter))
    {
        question->unit = pieces[pieces.size() - 1];
        pieces.pop_back();
    }
    else
    {
        question->unit = "";
    }
    iter = pieces.begin();
    if (searchInVector("is", pieces, iter))
    {
        pieces.erase(pieces.begin(), iter + 1);
        question->nums = pieces;
    }
    else
    {
        question->valid = false;
    }

    questions.push_back(question);
}

void InputReader::parseUnitInfo(vector<string>& pieces)
{
    Unit *unit = new Unit;
    pieces.pop_back(); // remove the "Credits"
    istringstream convert(pieces.back());
    if ( !(convert >> unit->value))
    {
        // invalid input
        return;
    }
    pieces.pop_back(); // remove value
    pieces.pop_back(); // remove the "is"
    string unitName = pieces.back();
    pieces.pop_back(); // remove unit name
    unit->nums = pieces;
    unitMap[unitName] = unit;
}

void InputReader::parseNumInfo(vector<string>& pieces)
{
    if (pieces.size() == 3)
        numberMap[pieces[0]] = pieces[2];
}

bool InputReader::searchInVector(const string& str, const vector<string>& pieces,
        vector<string>::iterator& i)
{
    while(i != pieces.end())
    {
        if (*i == str)
        {
            return true;
        }
        ++i;
    }
    return false;
}

