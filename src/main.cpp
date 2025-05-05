#include <iostream>
#include <string>
#include <simlib.h>
#include "MainCycle.hpp"

#define DEFAULT_NUMBER_OF_SOLAR_PANELS 8
#define DEFAULT_ENERGY_PRODUCTION_OF_SOLAR_PANEL_PER_YEAR 1     // in kWp
#define DEFAULT_HEAT_PUMP_POWER_CONSUMPTION 9
#define DEFAULT_HEAT_CONSUMPTION_KWH 4753
#define DEFAULT_AREA_OF_HOUSE 130  // m^2

using namespace std;

/**
 * @brief Prints help message
 */
void printHelp()
{
    cout << "Program for simulating energy production and consumpting it with heat pump." << endl << endl;

    cout << "Possible arguments:" << endl
            << "\t-p or --panels\t\t\tfor number of panels" << endl
            << "\t-pp or --panelProduction\tfor specifying production for one panel in kWp" << endl
            << "\t-a or --areaSpace\t\tfor area of house to experiment with in m^2" << endl
            << "\t-hc or --heatConsumption\tfor heat consumption of house per year in kWh" << endl
            << "\t-ch or --monthChoice\tfor month for simulating (1 - 12)" << endl
            << "\t-hpc or --heatPumpConsumption\tfor heat pump consumption per year in kWh" << endl
            << "\t-h or --help\t\t\tprints this message" << endl << endl;
}

/**
 * @brief Load arguments from command line
 * 
 * @param argc Number of arguments
 * @param argv List of arguments
 * @param panelsCount Pointer to panels count
 * @param panelProduction Pointer to panel production per year
 * @param areaSpace Pointer to size of building
 * @param heatConsumption Pointer to heat consumption per year
 */
bool loadArguments(
    int argc, 
    char *argv[], 
    unsigned int * panelsCount, 
    int * panelProduction, 
    unsigned int *areaSpace, 
    unsigned int * heatConsumption, 
    unsigned int * heatPumpConsumption,
    unsigned int * monthChoice)
{
    if (argc == 1)
    {
        cout << "You are running simulation with default values:" << endl
                << "Panels count: " << DEFAULT_NUMBER_OF_SOLAR_PANELS << endl
                << "Panel production: " << DEFAULT_ENERGY_PRODUCTION_OF_SOLAR_PANEL_PER_YEAR << " kWp" << endl
                << "House area: " << DEFAULT_AREA_OF_HOUSE << " m2" << endl
                << "Heat pump power consumption: " << DEFAULT_HEAT_PUMP_POWER_CONSUMPTION << " kWh" << endl << endl;
    }

    for (int i = 1; i < argc; i++)
    {
        string argument = argv[i];
        if (argument == "-p" || argument == "--panels")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set panels number
            try
            {
                *panelsCount = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }
        }
        else if (argument == "-pp" || argument == "--panelProduction")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set panel production
            try
            {
                *panelProduction = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }
        }
        else if (argument == "-a" || argument == "--areaSpace")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set area size
            try
            {
                *areaSpace = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }
        }
        else if (argument == "-hc" || argument == "--heatConsumption")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set heat consumption per year
            try
            {
                *heatConsumption = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }
        }
        else if (argument == "-ch" || argument == "--monthChoice")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set month choice
            try
            {
                *monthChoice = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }

            if (*monthChoice < 1 || 12 < *monthChoice)
            {
                cerr << "Wrong month choice!" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (argument == "-hpc" || argument == "--heatPumpConsumption")
        {
            if (i + 1 == argc)
            {
                cerr << "Wrong arguments count" << endl;
                return false;
            }

            // set heat pump consumption per year
            try
            {
                *heatPumpConsumption = stoi(argv[++i]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << endl;
                return false;
            }
        }
        else if (argument == "-h" || argument == "--help")
        {
            printHelp();
            exit(EXIT_SUCCESS);
        }
        else
        {
            cerr << "Unknown argument!";
            return false;
        }
    }

    return true;
}

/**
 * @brief Main function of the program
 * 
 * @param argc Arguments count
 * @param argv List of arguments
 * 
 * @return 0 if program terminates successfully or another number if not
 */
int main(int argc, char *argv[])
{
    unsigned int panelsCount = DEFAULT_NUMBER_OF_SOLAR_PANELS;
    int panelProduction = DEFAULT_ENERGY_PRODUCTION_OF_SOLAR_PANEL_PER_YEAR;
    unsigned int areaSpace = DEFAULT_AREA_OF_HOUSE;
    unsigned int heatConsumption = 0;
    unsigned int heatPumpConsumption = DEFAULT_HEAT_PUMP_POWER_CONSUMPTION;
    unsigned int monthChoice = 0;

    if (!loadArguments(argc, argv, &panelsCount, &panelProduction, &areaSpace, &heatConsumption, &heatPumpConsumption, &monthChoice))
    {
        return -1;
    }

    unsigned long fromAreaToEnergy;
    if (heatConsumption == 0)
    {
        heatConsumption = DEFAULT_HEAT_CONSUMPTION_KWH;
        auto spaceRatio = areaSpace / DEFAULT_AREA_OF_HOUSE;
        auto heatPumpConsumptionRatio = heatPumpConsumption / DEFAULT_HEAT_PUMP_POWER_CONSUMPTION;

        fromAreaToEnergy = ((heatConsumption * spaceRatio) * heatPumpConsumptionRatio);
    }
    else
    {
        fromAreaToEnergy = heatConsumption;
    }
    

    string heatConsumptionInfo = (heatConsumption > 0) ? ("Running experiment with " + to_string(heatConsumption) + " of house heat consumption\n") : "";

    cout << "---------------------------------------------------------------------" << endl
            << "SIMULATION START" << endl
            << "---------------------------------------------------------------------" << endl
            << "Running experiment with " << panelsCount << " panels count." << endl
            << "Running experiment with " << panelProduction << " kWp one panel production per year." << endl
            << "Running experiment with expected heat consumption " << fromAreaToEnergy << " kWh" << endl
            << "---------------------------------------------------------------------" << endl << endl;

    // Simulation time is in hours
    Init(0.0, 32*24);

    // Main cycle
    (new MainCycle(
        panelsCount * panelProduction,
        fromAreaToEnergy,
        monthChoice
    ))->Activate();

    Run();
    SIMLIB_statistics.Output();

    cout << "---------------------------------------------------------------------" << endl
            << "SIMULATION END" << endl
            << "---------------------------------------------------------------------" << endl << endl;

    return 0;
}
