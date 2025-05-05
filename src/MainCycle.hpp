#ifndef MAIN_CYCLE_HPP
#define MAIN_CYCLE_HPP

#include <simlib.h>

class MainCycle : public Process
{
private:
    const double PERIOD_DIVISION = 30;

    unsigned long *panelsProduction;
    unsigned long *heatConsumptionPerYear;

    unsigned int choice;
    
    Store *heatPumps;

    // Stats
    Stat *heatPumpConsumptionStat;

    void PrintStartOfCycle();

    void PrintEndOfCycle();
public:
    MainCycle(unsigned int panelEnergyProductionInKwp, unsigned int heatConsumptionDifficulty, unsigned int monthChoice);
    ~MainCycle() override;
    void Behavior() override;
};

#endif
