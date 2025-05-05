#ifndef HEAT_PUMP_HPP
#define HEAT_PUMP_HPP

#include <simlib.h>

class HeatPump : public Process
{
private:
    Store *heatPumps;

    const double HEAT_PUMP_DURATION = 24;
public:
    HeatPump(
        Store *heatPumps
    );
    
    void Behavior() override;
};

#endif //HEAT_PUMP_HPP
