#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include <string>
using namespace std;

struct Resident {
    string id;
    int age;
    string modeOfTransport;
    double dailyDistance;
    double carbonEmissionFactor;
    int averageDayPerMonth;
};

// Function prototypes
int readCSV(const string& filename, Resident residents[], int maxSize);
void analyzeAgeGroup(Resident residents[], int size, int minAge, int maxAge, const string& groupName);

#endif
