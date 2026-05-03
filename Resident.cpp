#define _HAS_STD_BYTE 0

#include "recordArray.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// ============================================================
//  Helper
// ============================================================
void printSeparator(int width) {
    cout << string(width, '-') << "\n";
}

// ============================================================
//  readCSV
//  Parses by column position so it works for all 3 CSV files
//  regardless of their slightly different header names.
// ============================================================
int readCSV(const string& filename, Resident residents[], int maxSize) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[ERROR] Cannot open file: " << filename << "\n";
        return 0;
    }

    string line;
    getline(file, line); // skip header

    int count = 0;
    while (getline(file, line) && count < maxSize) {
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;

        getline(ss, residents[count].id, ',');

        getline(ss, temp, ',');
        try { residents[count].age = stoi(temp); }
        catch (...) { continue; }

        getline(ss, residents[count].modeOfTransport, ',');

        getline(ss, temp, ',');
        try { residents[count].dailyDistance = stod(temp); }
        catch (...) { continue; }

        getline(ss, temp, ',');
        try { residents[count].carbonEmissionFactor = stod(temp); }
        catch (...) { continue; }

        getline(ss, temp, ',');
        try { residents[count].averageDayPerMonth = stoi(temp); }
        catch (...) { continue; }

        count++;
    }
    return count;
}

// ============================================================
//  TASK 4 - Age Group Analysis
//  Linear search through unsorted array for each age group.
//  Finds: most preferred transport, total emission, average
//  emission per resident.
// ============================================================
void analyzeAllAgeGroups(Resident residents[], int size,
    const string& datasetName) {
    cout << "\n";
    printSeparator(72);
    cout << "  AGE GROUP ANALYSIS  |  Dataset: " << datasetName << "\n";
    printSeparator(72);

    for (int g = 0; g < NUM_AGE_GROUPS; g++) {
        int    groupCount = 0;
        double totalEmission = 0.0;
        int    modeCnt[NUM_MODES] = {};
        double modeEmission[NUM_MODES] = {};

        // Linear search - unsorted array
        for (int i = 0; i < size; i++) {
            if (residents[i].age >= AGE_MIN[g] &&
                residents[i].age <= AGE_MAX[g]) {

                double em = residents[i].monthlyEmission();
                totalEmission += em;
                groupCount++;

                // Tally by transport mode
                for (int m = 0; m < NUM_MODES; m++) {
                    if (residents[i].modeOfTransport == MODES[m]) {
                        modeCnt[m]++;
                        modeEmission[m] += em;
                        break;
                    }
                }
            }
        }

        cout << "\nAge Group : " << AGE_LABEL[g] << "\n";
        printSeparator(72);

        if (groupCount == 0) {
            cout << "  No residents found in this age group.\n";
            continue;
        }

        // Find most preferred mode
        int bestMode = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (modeCnt[m] > modeCnt[bestMode])
                bestMode = m;

        // Print table
        cout << left
            << setw(16) << "Mode"
            << setw(8) << "Count"
            << setw(22) << "Total Emission (kg)"
            << setw(22) << "Avg per Resident (kg)"
            << "\n";
        printSeparator(72);

        for (int m = 0; m < NUM_MODES; m++) {
            if (modeCnt[m] == 0) continue;
            double avg = modeEmission[m] / modeCnt[m];
            cout << left
                << setw(16) << MODES[m]
                << setw(8) << modeCnt[m]
                << setw(22) << fixed << setprecision(2) << modeEmission[m]
                << setw(22) << avg
                << "\n";
        }

        printSeparator(72);
        cout << "  Total residents     : " << groupCount << "\n";
        cout << "  Most preferred mode : " << MODES[bestMode]
            << " (" << modeCnt[bestMode] << " residents)\n";
        cout << "  Total emission      : " << fixed << setprecision(2)
            << totalEmission << " kg CO2\n";
        cout << "  Average emission    : "
            << (totalEmission / groupCount) << " kg CO2 per resident\n";
    }
}

// ============================================================
//  TASK 7a - Search by Age Group (linear search)
// ============================================================
void searchByAgeGroup(Resident residents[], int size, int groupIndex) {
    if (groupIndex < 0 || groupIndex >= NUM_AGE_GROUPS) {
        cout << "[ERROR] Invalid age group selection.\n";
        return;
    }

    cout << "\n";
    printSeparator(72);
    cout << "  SEARCH BY AGE GROUP\n";
    cout << "  Group : " << AGE_LABEL[groupIndex] << "\n";
    printSeparator(72);
    cout << left
        << setw(10) << "ID"
        << setw(6) << "Age"
        << setw(14) << "Transport"
        << setw(12) << "Dist (km)"
        << setw(8) << "Days"
        << setw(16) << "Emission (kg)"
        << "\n";
    printSeparator(72);

    int found = 0;
    for (int i = 0; i < size; i++) {
        if (residents[i].age >= AGE_MIN[groupIndex] &&
            residents[i].age <= AGE_MAX[groupIndex]) {
            cout << left
                << setw(10) << residents[i].id
                << setw(6) << residents[i].age
                << setw(14) << residents[i].modeOfTransport
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(8) << residents[i].averageDayPerMonth
                << setw(16) << residents[i].monthlyEmission()
                << "\n";
            found++;
        }
    }

    printSeparator(72);
    cout << "  Records found: " << found << "\n";
}

// ============================================================
//  TASK 7b - Search by Transport Mode (linear search)
// ============================================================
void searchByTransport(Resident residents[], int size, const string& mode) {
    cout << "\n";
    printSeparator(72);
    cout << "  SEARCH BY TRANSPORT MODE\n";
    cout << "  Mode : " << mode << "\n";
    printSeparator(72);
    cout << left
        << setw(10) << "ID"
        << setw(6) << "Age"
        << setw(12) << "Dist (km)"
        << setw(8) << "Days"
        << setw(16) << "Emission (kg)"
        << "\n";
    printSeparator(72);

    int found = 0;
    for (int i = 0; i < size; i++) {
        if (residents[i].modeOfTransport == mode) {
            cout << left
                << setw(10) << residents[i].id
                << setw(6) << residents[i].age
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(8) << residents[i].averageDayPerMonth
                << setw(16) << residents[i].monthlyEmission()
                << "\n";
            found++;
        }
    }

    printSeparator(72);
    cout << "  Records found: " << found << "\n";
}

// ============================================================
//  TASK 7c - Search by Daily Distance Threshold (linear search)
// ============================================================
void searchByDistance(Resident residents[], int size, double threshold) {
    cout << "\n";
    printSeparator(72);
    cout << "  SEARCH BY DAILY DISTANCE THRESHOLD\n";
    cout << "  Showing residents with daily distance > "
        << fixed << setprecision(1) << threshold << " km\n";
    printSeparator(72);
    cout << left
        << setw(10) << "ID"
        << setw(6) << "Age"
        << setw(14) << "Transport"
        << setw(12) << "Dist (km)"
        << setw(16) << "Emission (kg)"
        << "\n";
    printSeparator(72);

    int found = 0;
    for (int i = 0; i < size; i++) {
        if (residents[i].dailyDistance > threshold) {
            cout << left
                << setw(10) << residents[i].id
                << setw(6) << residents[i].age
                << setw(14) << residents[i].modeOfTransport
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(16) << residents[i].monthlyEmission()
                << "\n";
            found++;
        }
    }

    printSeparator(72);
    cout << "  Records found: " << found << "\n";
}