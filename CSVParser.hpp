#pragma once

#include "ResidentArray.hpp"

double computeMonthlyEmissions(double dailyDistance, double emissionFactor, int averageDaysPerMonth);

bool parseResidentCsvLine(const char* line, Resident& outResident);

bool loadCsvToArray(const char* filePath, ResidentArray& outArray);
