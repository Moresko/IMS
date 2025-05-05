#include "HeatPump.hpp"

HeatPump::HeatPump(
    Store *heatPumps
) : 
    heatPumps(heatPumps)
{
}

void HeatPump::Behavior()
{
    Wait(HEAT_PUMP_DURATION);

    Leave(*heatPumps, 1);
}
