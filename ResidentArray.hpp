#ifndef RESIDENT_ARRAY_HPP
#define RESIDENT_ARRAY_HPP

#pragma once
#include <string>
#include "Resident.hpp"

struct ResidentArray {
    Resident* arr;
    int size;
    int capacity;
};



// ============================================================
//  Constants
// ============================================================
const int MAX_RESIDENTS = 300;

const int         NUM_MODES = 6;
const std::string MODES[NUM_MODES] = {
    "Bicycle", "Bus", "Car", "Carpool", "School Bus", "Walking"
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
//  Functions
// ============================================================
// UNSORTED ARRAY FUNCTIONS
void analyzeAllAgeGroups(Resident residents[], int size, const std::string& datasetName);

ResidentArray searchByAgeGroup(const ResidentArray& input, int groupIndex);
ResidentArray searchByTransport(const ResidentArray& input, const std::string& mode);
ResidentArray searchByDistance(const ResidentArray& input, double minDistance, double maxDistance);
ResidentArray searchByEmission(const ResidentArray& input, double threshold);

// SORTED ARRAY FUNCTIONS
void binarySearchByAge(const ResidentArray& resident, int minAge, int maxAge);

void binarySearchByDistance(const ResidentArray& resident, double minDistanceExclusive);

void binarySearchByEmission(const ResidentArray& resident, double emissionThreshold);



// UTILITY FUNCTIONS
void printResidentArray(const ResidentArray& arr);

#endif