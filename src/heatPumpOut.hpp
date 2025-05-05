#ifndef HEAT_PUMP_OUT_HPP
#define HEAT_PUMP_OUT_HPP

#include <simlib.h>
#include "MainCycle.hpp"

class heatPumpOut : public Event
{
public:
    explicit heatPumpOut(MainCycle *mainCycle);
    
    void Behavior() override;
private:
    // 1 month is approximately 720 hours
    // double heatPumpWait = Normal(732,12);
    const double MONTH_DURATION = 720;

    MainCycle *mainCycle;

    void printHeatPumpOut();
};

#endif
