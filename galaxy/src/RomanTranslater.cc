/**
 * @file RomanTranslater.cc
 * @brief translate Roman numerals to Arabic numerals
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include "RomanTranslater.h"

RomanTranslater* RomanTranslater::m_ins = NULL;
auto_ptr<RomanTranslater> RomanTranslater::m_auto_ptr;
RomanTranslater::RomanTranslater()
{
    m_auto_ptr = auto_ptr<RomanTranslater>(this);
}
RomanTranslater::~RomanTranslater()
{
}
RomanTranslater* RomanTranslater::Ins()
{
    if ( m_ins == NULL)
        m_ins = new RomanTranslater();
    return m_ins;
}

void RomanTranslater::invalidCheckLetterIssue(string romanNum, string* invalidPieces,
        unsigned int sizeOfInvalidPieces)
{
    // These number should not exist in Roman numberials
    for (unsigned int i = 0; i < sizeOfInvalidPieces; ++i)
    {
        if (romanNum.find(invalidPieces[i]) != string::npos )
            throw InvalidRomanNumberException("Invalid Roman number.");
    }
}

void RomanTranslater::invalidCheckOverLetter(string romanNum)
{
    string invalidPieces[] = {"IC", "ID", "VC", "VD", "XM", "LM", "IM", "VM"};
    unsigned int sizeOfInvalidPieces = sizeof(invalidPieces) / sizeof(string);
    invalidCheckLetterIssue(romanNum, invalidPieces, sizeOfInvalidPieces);
}

void RomanTranslater::invalidCheckDuplicatedLetter(string romanNum)
{
    // These number should not exist in Roman numberials
    string invalidPieces[] = {"MMMM", "DD", "CCCC", "LL", "XXXX", "VV", "IIII"};
    unsigned int sizeOfInvalidPieces = sizeof(invalidPieces) / sizeof(string);
    invalidCheckLetterIssue(romanNum, invalidPieces, sizeOfInvalidPieces);
}

int RomanTranslater::Translate(string romanIn)
{
    int* dec = new int[romanIn.size()];
    int result = 0;

    if (romanIn == "")
        throw InvalidRomanNumberException("Empty input number.");

    invalidCheckDuplicatedLetter(romanIn);
    invalidCheckOverLetter(romanIn);

    for(unsigned int i = 0; i<romanIn.size(); ++i)
    {
        switch(romanIn[i])
        {
            case 'M':
                dec[i] = 1000;
                break;
            case 'D':
                dec[i] = 500;
                break;
            case 'C':
                dec[i] = 100;
                break;
            case 'L':
                dec[i] = 50;
                break;
            case 'X':
                dec[i] = 10;
                break;
            case 'V':
                dec[i] = 5;
                break;
                break;
            case 'I':
                dec[i] = 1;
                break;
            default:
                throw InvalidRomanNumberException("Not a Roman number.");
        }
    }

    for (unsigned int i = 0; i<romanIn.size()-1; ++i)
    {
        if(dec[i] < dec[i+1])
            result -= dec[i];
        else
            result += dec[i];
    }
    result += dec[romanIn.size()-1];

    delete [] dec;
    return result;
}

