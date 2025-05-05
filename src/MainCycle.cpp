#include <iostream>
#include "MainCycle.hpp"
#include "heatPumpOut.hpp"
#include "HeatPump.hpp"
#include "time.h"
#include <random>

using namespace std;

#define ENERGY_WINTER 35.8700
#define ENERGY_POST_WINTER 62.4200
#define ENERGY_PRE_SUMMER 93.440
#define ENERGY_SUMMER 119.1800

#define ENERGY_PRODUCTION_DEVIATION_PERCENTAGE 0.1666667

#define CONSUMPTION_WINTER_PERCENT 824.333 / 5331
#define CONSUMPTION_POST_WINTER_PERCENT 820.0 / 5331
#define CONSUMPTION_PRE_SUMMER_PERCENT 313.5 / 5331
#define CONSUMPTION_SUMMER_PERCENT 118.2 / 5331

#define CONSUMPTION_DEVIATION_PERCENTAGE_WINTER 0.0633333
#define CONSUMPTION_DEVIATION_PERCENTAGE_POST_WINTER 0.315
#define CONSUMPTION_DEVIATION_PERCENTAGE_PRE_SUMMER 0.7
#define CONSUMPTION_DEVIATION_PERCENTAGE_SUMMER 0.184

string getMonthFromChoice (unsigned int choice)
{
    switch (choice) {
        case 1:
            return "January";
            break;
        case 2:
            return "February";
            break;
        case 3:
            return "March";
            break;
        case 4:
            return "April";
            break;
        case 5:
            return "May";
            break;
        case 6:
            return "June";
            break;
        case 7:
            return "July";
            break;
        case 8:
            return "August";
            break;
        case 9:
            return "September";
            break;
        case 10:
            return "October";
            break;
        case 11:
            return "November";
            break;
        case 12:
            return "December";
            break;
    }

    return "";
}

double getNormalConsumption (double value, double deviationPercentage)
{
    double deviationValue = deviationPercentage * value;

    default_random_engine generator;
    normal_distribution<double> dist(value, deviationValue);

    return dist(generator);
}

double getMonthProductionByChoice(int choice, double panelsProduction)
{
    double energy_month;
    switch (choice) {
        case 1:
        case 11:
        case 12:
            energy_month = ENERGY_WINTER * panelsProduction;
            return getNormalConsumption(energy_month, ENERGY_PRODUCTION_DEVIATION_PERCENTAGE);
            break;
        case 2:
        case 10:
            energy_month = ENERGY_POST_WINTER * panelsProduction;
            return getNormalConsumption(energy_month, ENERGY_PRODUCTION_DEVIATION_PERCENTAGE);
            break;
        case 3:
        case 9:
            energy_month = ENERGY_PRE_SUMMER * panelsProduction;
            return getNormalConsumption(energy_month, ENERGY_PRODUCTION_DEVIATION_PERCENTAGE);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            energy_month = ENERGY_SUMMER * panelsProduction;
            return getNormalConsumption(energy_month, ENERGY_PRODUCTION_DEVIATION_PERCENTAGE);
            break;
    }

    return 0.0;
}

double getMonthConsumptionByChoice(int choice, double heatConsumptionYear)
{
    double energy_month;
    switch (choice) {
        case 1:
        case 11:
        case 12:
            energy_month = CONSUMPTION_WINTER_PERCENT * heatConsumptionYear;
            return getNormalConsumption(energy_month, CONSUMPTION_DEVIATION_PERCENTAGE_WINTER);
            break;
        case 2:
        case 10:
            energy_month = CONSUMPTION_POST_WINTER_PERCENT * heatConsumptionYear;
            return getNormalConsumption(energy_month, CONSUMPTION_DEVIATION_PERCENTAGE_POST_WINTER);
            break;
        case 3:
        case 9:
            energy_month = CONSUMPTION_PRE_SUMMER_PERCENT * heatConsumptionYear;
            return getNormalConsumption(energy_month, CONSUMPTION_DEVIATION_PERCENTAGE_PRE_SUMMER);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            auto energy_month = CONSUMPTION_SUMMER_PERCENT * heatConsumptionYear;
            return getNormalConsumption(energy_month, CONSUMPTION_DEVIATION_PERCENTAGE_SUMMER);
            break;
    }

    return 0.0;
}

MainCycle::MainCycle(
    unsigned int panelEnergyProductionInKwp, 
    unsigned int heatConsumptionDifficulty,
    unsigned int monthChoice
)
{
    // Store
    this->heatPumps = new Store("Heat pumps storage", 1);

    // Stats
    heatPumpConsumptionStat = new Stat("Heat pump consumption per day in kWh");

    // Numbers
    panelsProduction = new unsigned long(static_cast<unsigned long>(panelEnergyProductionInKwp));
    heatConsumptionPerYear = new unsigned long(static_cast<unsigned long>(heatConsumptionDifficulty));

    choice = monthChoice;

    PrintStartOfCycle();
}

MainCycle::~MainCycle()
{
    PrintEndOfCycle();

    // Numbers
    delete panelsProduction;
    delete heatConsumptionPerYear;

    // Stats
    delete heatPumpConsumptionStat;
}

void MainCycle::Behavior()
{
    // Heat pump enduration event
    auto *heatPumpOutTimer = new heatPumpOut(this);

    // Randomize
    srand((unsigned)time(NULL));

    if (choice == 0)
    {
        // Random choice 1 - 12
        choice = (rand() % 12) + 1;
    }

    double energy_producted_month = getMonthProductionByChoice(choice, (*panelsProduction));
    double energy_consumption_month = getMonthConsumptionByChoice(choice, (*heatConsumptionPerYear));

    // Daily deviation
    double deviation = 0.1;
    auto energy_consumption_day = getNormalConsumption(energy_consumption_month / PERIOD_DIVISION, deviation);

    while (energy_producted_month >= energy_consumption_day)
    {
        Enter(*heatPumps, 1);

        (*heatPumpConsumptionStat)(energy_consumption_day);
        energy_producted_month -= energy_consumption_day;

        (new HeatPump(
            heatPumps
        ))->Activate();

        energy_consumption_day = getNormalConsumption(energy_consumption_month / PERIOD_DIVISION, deviation);
    }

    Enter(*heatPumps, 1);
    Leave(*heatPumps, 1);

    delete heatPumpOutTimer;
}

void MainCycle::PrintStartOfCycle()
{
    cout << "--------------------------------------------" << endl
            << "Main cycle started" << endl
            << "Start time: " << Time << endl
            << "One panel production: " << *panelsProduction << " kWp" << endl
            << "Expected energy consumption per year: " << (*heatConsumptionPerYear) << " kWh" << endl
            << "--------------------------------------------" << endl << endl;
}

void MainCycle::PrintEndOfCycle()
{
    cout << "--------------------------------------------" << endl
            << "Main cycle finished" << endl;

    cout << "Month: " << getMonthFromChoice(choice) << endl;

    heatPumps->Output();
    
    heatPumpConsumptionStat->Output();

    cout << "--------------------------------------------" << endl << endl;
}
