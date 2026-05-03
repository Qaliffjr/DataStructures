#pragma once
#include <string>

struct Resident {
    std::string ID;
    int Age;
    std::string modeOfTransport;
    double dailyDistance;
    double carbonEmissionFactor;
    int averageDayPerMonth;
    double monthlyCarbonEmission;
};
