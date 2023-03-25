

#include <iostream>
#include <string>
#include "Histogram.h"
#include "RandomEintegerGenerator.h"

using namespace Hist;
using namespace std;

const int GENERATE_COUNT = 20;

int main()
{
    unique_ptr<Logger> logger = std::make_unique<Logger>();
    RandomEintegerGenerator gen;
    Histogram hist(std::move(logger));

    for (int i = 0; i < GENERATE_COUNT; i++)
    {
        EInteger rndNum = gen();
        try {
            hist.add(rndNum);
        }
        catch (out_of_range& e) {
            cout << "Caught out_of_range exception" << endl << e.what();
            cout << e.what();
        }
    }
    try {
        EInteger min = hist.getMinValue();
        EInteger max = hist.getMaxValue();
        EInteger avg = hist.getMode();
        cout << "Average value:" << avg;
    }
    catch (length_error& e) {
        cout << "Caught length_error exception" << endl << e.what();
        cout << e.what();
    }
}

