#pragma once
#include <string>
using namespace std;

struct Resident {
};

// Function prototypes
int readCSV(const string& filename, Resident residents[], int maxSize);
void analyzeAgeGroup(Resident residents[], int size, int minAge, int maxAge, const string& groupName);

#endif
