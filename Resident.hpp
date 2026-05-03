#pragma once
#include <string>

struct Resident {
    std::string ID;
    int Age;
    std::string modeOfTransport;
    int dailyDistance;
    double carbonEmission;
    int monthlyFrequency;
    double monthlyCarbonEmission;
};
