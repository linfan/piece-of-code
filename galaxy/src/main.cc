/**
 * @file main.cc
 * @brief galaxy merchant program entry
 *
 * @author LinFan
 * @version 1.0.0
 * @internal
 * Email: linfan.china@gmail.com
 */

#include "GalaxyTranslater.h"
#include "InputReader.h"
#include "RomanTranslater.h"
#include "OutputCalculator.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <InputFile>" << endl;
        return -1;
    }

    InputReader reader;
    reader.ParseFile(argv[1]);

    OutputCalculator calc;
    calc.SetInputInfo(reader.GetInputInformation());
    calc.AnswerQuestions();
    return 0;
}
