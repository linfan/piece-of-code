/**
 * @file GalaxyTranslater.cc
 * @brief translate Galaxy numerals to standard Roman numerals
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include "GalaxyTranslater.h"

GalaxyTranslater* GalaxyTranslater::m_ins = NULL;
auto_ptr<GalaxyTranslater> GalaxyTranslater::m_auto_ptr;
GalaxyTranslater::GalaxyTranslater()
{
    m_auto_ptr = auto_ptr<GalaxyTranslater>(this);
}
GalaxyTranslater::~GalaxyTranslater()
{
}
GalaxyTranslater* GalaxyTranslater::Ins()
{
    if ( m_ins == NULL)
        m_ins = new GalaxyTranslater();
    return m_ins;
}

string GalaxyTranslater::Translate(const vector<string>& galaxyNum, 
        const map<string, string>& dict)
{
    string romanNum = "";
    for_each (galaxyNum.begin(), galaxyNum.end(),
        [&dict, &romanNum] (string galNum) {
            try {
                string roNum = dict.at(galNum);
                if (roNum == "")
                    throw InvalidGalaxyNumberException("Dictionary contain empty mapping.");
                romanNum += roNum;
            } catch (const out_of_range& e) {
                throw InvalidGalaxyNumberException("Number " + galNum + " not exist.");
            }
        }
    );
    return romanNum;
}

