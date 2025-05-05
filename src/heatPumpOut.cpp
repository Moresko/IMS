#include <iostream>
#include "heatPumpOut.hpp"

using namespace std;

heatPumpOut::heatPumpOut(MainCycle *mainCycle) : mainCycle(mainCycle)
{
    Activate(Time + MONTH_DURATION);
}

void heatPumpOut::Behavior()
{
    printHeatPumpOut();
    
    delete mainCycle;
}

void heatPumpOut::printHeatPumpOut()
{
    cout << "Heat pump endures whole month." << endl
            << "--------------------------------------------" << endl << endl;
}
