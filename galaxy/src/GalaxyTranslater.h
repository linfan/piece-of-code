/**
 * @file GalaxyTranslater.h
 * @brief translate Galaxy numerals to standard Roman numerals
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#ifndef _GALAXY_TRANSLATER_H_
#define _GALAXY_TRANSLATER_H_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

/**
 @class InvalidGalaxyNumberException
 @brief Exception class identify error on Galaxy number converting
 */
class InvalidGalaxyNumberException
{
    private:
        string reason;
    public:
        InvalidGalaxyNumberException(string str)
            : reason(str)
        {}
        string GetReason()
        { return reason; }
};

/**
 @class GalaxyTranslater
 @brief Singleton class translate Galaxy number to Roman number
 */
class GalaxyTranslater
{
    private:
        static auto_ptr<GalaxyTranslater> m_auto_ptr;
        static GalaxyTranslater * m_ins;
    protected:
        GalaxyTranslater();
        GalaxyTranslater(const GalaxyTranslater&);
        virtual ~GalaxyTranslater();
        friend class auto_ptr<GalaxyTranslater>; 
    public:
        /** Get singleton instance
         */
        static GalaxyTranslater * Ins();
        /** Do translate
         * @param galaxyNum vector of Galaxy letters
         * @param dict mapping of Galaxy letter and Roman letter
         * @return string of translated Roman number
         */
        string Translate(const vector<string>& galaxyNum, 
                const map<string, string>& dict);
};

#endif // _GALAXY_TRANSLATER_H_

