#ifndef RECORDARRAY_HPP
#define RECORDARRAY_HPP

#include <string>

// ============================================================
//  Resident struct
// ============================================================
struct Resident {
    std::string id;
    int         age;
    std::string modeOfTransport;
    double      dailyDistance;
    double      carbonEmissionFactor;
    int         averageDayPerMonth;

    double monthlyEmission() const {
        return dailyDistance * carbonEmissionFactor * averageDayPerMonth;
    }
};

// ============================================================
//  Constants
// ============================================================
const int MAX_RESIDENTS = 300;

const int         NUM_MODES = 6;
const std::string MODES[NUM_MODES] = {
    "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
};

const int         NUM_AGE_GROUPS = 5;
const int         AGE_MIN[NUM_AGE_GROUPS] = { 6, 18, 26, 46,  61 };
const int         AGE_MAX[NUM_AGE_GROUPS] = { 17, 25, 45, 60, 100 };
const std::string AGE_LABEL[NUM_AGE_GROUPS] = {
    "Children & Teenagers (6-17)",
    "University Students / Young Adults (18-25)",
    "Working Adults - Early Career (26-45)",
    "Working Adults - Late Career (46-60)",
    "Senior Citizens / Retirees (61-100)"
};

// ============================================================
//  Function prototypes
// ============================================================
int  readCSV(const std::string& filename, Resident residents[], int maxSize);

void analyzeAllAgeGroups(Resident residents[], int size, const std::string& datasetName);

void searchByAgeGroup(Resident residents[], int size, int groupIndex);
void searchByTransport(Resident residents[], int size, const std::string& mode);
void searchByDistance(Resident residents[], int size, double threshold);

void printSeparator(int width = 72);

#endif