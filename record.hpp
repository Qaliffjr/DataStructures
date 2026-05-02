#pragma once
#include <string>

struct Record {
    std::string ID;
    int Age;
    std::string modeOfTransport;
    int dailyDistance;
    double carbonEmission;
    int monthlyFrequency;
    double monthlyCarbonEmission;
};
