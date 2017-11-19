/**
 * @file RomanTranslater.h
 * @brief translate Roman numerals to Arabic numerals
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#ifndef _ROMAN_TRANSLATER_H_
#define _ROMAN_TRANSLATER_H_

#include <iostream>
#include <string>
#include <memory>
using namespace std;

/** @class InvalidRomanNumberException
 * @brief Exception class identify error on Roman number converting
 */
class InvalidRomanNumberException
{
    private:
        string reason;
    public:
        InvalidRomanNumberException(string str)
            : reason(str)
        {}
        string GetReason()
        { return reason; }
};

/** @class RomanTranslater
 * @brief Singleton class translate Roman number to Arabic number
 */
class RomanTranslater
{
    private:
        static auto_ptr<RomanTranslater> m_auto_ptr;
        static RomanTranslater * m_ins;
    protected:
        RomanTranslater();
        RomanTranslater(const RomanTranslater&);
        void invalidCheckLetterIssue(string , string*, unsigned int);
        void invalidCheckDuplicatedLetter(string romanNum);
        void invalidCheckOverLetter(string romanNum);
        virtual ~RomanTranslater();
        friend class auto_ptr<RomanTranslater>;
    public:
        /** Get singleton instance
         */
        static RomanTranslater * Ins();
        /** Do translate
         * @param romanIn string of Roman number to translate
         * @return value of Arabic number
         */
        int Translate(string romanIn);
};

#endif // _ROMAN_TRANSLATER_H_
