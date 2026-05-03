#define _HAS_STD_BYTE 0

#include "ResidentArray.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "tableDisplay.hpp"
using namespace std;

// ============================================================
//  Helper
// ============================================================

struct result {
    string mode;
    double totalEmission;
    double avgEmission;
    int count;
};
// ============================================================
//  TASK 4 - Age Group Analysis
//  Linear search through unsorted array for each age group.
//  Finds: most preferred transport, total emission, average
//  emission per resident.
// ============================================================

void analyzeAllAgeGroups(Resident residents[], int size, const string& datasetName) {

    cout << "\n";
    printSeparator(72);
    cout << "  AGE GROUP ANALYSIS  |  Dataset: " << datasetName << "\n";
    printSeparator(72);

    //Prepare Table
    const int COLS = 5;

    std::string headers[COLS] = {
        "Category",
        "Preferred Mode of Transport",
        "Total Carbon Emission",
        "Average Emission per Resident",
        "Number of Resident"
    };

    int widths[COLS] = {
    50,  // Category
    28,  // Preferred Mode
    22,  // Total Emission
    30,  // Avg Emission
    20   // Number of Resident
    };
    std::string rows[5][10];
    int rowCount = 0;
    int groupCount = 0;

    for (int g = 0; g < NUM_AGE_GROUPS; g++) {
        rowCount++;
        int groupCount = 0;
        double totalEmission = 0.0;
        int modeCnt[NUM_MODES] = {};

        int minAge = AGE_MIN[g];
        int maxAge = AGE_MAX[g];

        auto programStart = chrono::high_resolution_clock::now();
        // =========================
        // Linear search (unsorted array)
        // =========================
        for (int i = 0; i < size; i++) {

            if (residents[i].Age >= minAge &&
                residents[i].Age <= maxAge) {

                double em = residents[i].monthlyCarbonEmission;
                totalEmission += em;
                groupCount++;

                // Count transport modes
                for (int m = 0; m < NUM_MODES; m++) {
                    if (residents[i].modeOfTransport == MODES[m]) {
                        modeCnt[m]++;
                        break;
                    }
                }
            }
        }
        if (groupCount == 0) {
            cout << "  No residents found in this age group.\n";
            return;
        }

        // =========================
        // Find most preferred mode
        // =========================
        int bestMode = 0;
        for (int m = 1; m < NUM_MODES; m++) {
            if (modeCnt[m] > modeCnt[bestMode]) {
                bestMode = m;
            }
        }
        auto programEnd = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = programEnd - programStart;

        // Insert into Table
        rows[rowCount][0] = AGE_LABEL[g];
        rows[rowCount][1] = MODES[bestMode];
        rows[rowCount][2] = totalEmission;
        rows[rowCount][3] = totalEmission / groupCount;
        rows[rowCount][4] = std::to_string(groupCount);
        rowCount++;
    }
    printTable(headers, COLS, rows, rowCount, widths);
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
        if (residents[i].Age >= AGE_MIN[groupIndex] &&
            residents[i].Age <= AGE_MAX[groupIndex]) {
            cout << left
                << setw(10) << residents[i].ID
                << setw(6) << residents[i].Age
                << setw(14) << residents[i].modeOfTransport
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(8) << residents[i].monthlyFrequency
                << setw(16) << residents[i].monthlyCarbonEmission
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
                << setw(10) << residents[i].ID
                << setw(6) << residents[i].Age
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(8) << residents[i].monthlyFrequency
                << setw(16) << residents[i].monthlyCarbonEmission
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
                << setw(10) << residents[i].ID
                << setw(6) << residents[i].Age
                << setw(14) << residents[i].modeOfTransport
                << setw(12) << fixed << setprecision(1) << residents[i].dailyDistance
                << setw(16) << residents[i].monthlyCarbonEmission
                << "\n";
            found++;
        }
    }

    printSeparator(72);
    cout << "  Records found: " << found << "\n";
}