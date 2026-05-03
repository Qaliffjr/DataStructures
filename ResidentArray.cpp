#define _HAS_STD_BYTE 0

#include "ResidentArray.hpp"
#include "ResidentArrayUtils.hpp"
#include "tableDisplay.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
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

    cout << "\n\n\n";
    printSeparator(72);
    cout << "AGE GROUP ANALYSIS  |  Dataset: " << datasetName << "\n";

    //Prepare Table
    const int COLS = 5;

    std::string headers[COLS] = {
        "Category",
        "Preferred Transport Mode",
        "Total Carbon Emission",
        "Average Emission",
        "Number of Resident"
    };

    int widths[COLS] = {
    50,  // Category
    30,  // Preferred Mode
    24,  // Total Emission
    24,  // Avg Emission
    20   // Number of Resident
    };
    std::string rows[5][10];
    int rowCount = 0;
    int groupCount = 0;

    auto programStart = chrono::high_resolution_clock::now();

    for (int g = 0; g < NUM_AGE_GROUPS; g++) {
        rowCount++;
        groupCount = 0;
        double totalEmission = 0.0;
        int modeCnt[NUM_MODES] = {};

        int minAge = AGE_MIN[g];
        int maxAge = AGE_MAX[g];

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
        // =========================
        // Find most preferred mode
        // =========================
        int bestMode = 0;
        for (int m = 1; m < NUM_MODES; m++) {
            if (modeCnt[m] > modeCnt[bestMode]) {
                bestMode = m;
            }
        }
        // Insert into Table
        rows[g][0] = AGE_LABEL[g];
        rows[g][1] = MODES[bestMode];
        rows[g][2] = to_string(totalEmission);
        double avg = (groupCount == 0) ? 0 : (totalEmission / groupCount);
        rows[g][3] = to_string(avg);
        rows[g][4] = std::to_string(groupCount);
    }
    printTable(headers, COLS, rows, rowCount, widths);
    auto programEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = programEnd - programStart;
	std::cout << "[Process time: " << fixed << setprecision(4) << elapsed.count() << " ms]\n";
}



// Unsorted Search (Linear Search)
ResidentArray searchByAgeGroup(const ResidentArray& input, int groupIndex) {
    ResidentArray result;

    // handle invalid group
    if (groupIndex < 0 || groupIndex >= NUM_AGE_GROUPS) {
        initResidentArray(result, 1);
        return result;
    }

    // start with small capacity (like empty list growing)
    initResidentArray(result, 2);

    int minAge = AGE_MIN[groupIndex];
    int maxAge = AGE_MAX[groupIndex];

    for (int i = 0; i < input.size; i++) {
        int age = input.arr[i].Age;

        if (age >= minAge && age <= maxAge) {

            // resize if full (like list automatically growing)
            if (result.size == result.capacity) {
                int newCap = result.capacity * 2;

                Resident* newArr = new Resident[newCap];

                for (int j = 0; j < result.size; j++) {
                    newArr[j] = result.arr[j];
                }

                delete[] result.arr;
                result.arr = newArr;
                result.capacity = newCap;
            }

            // insert (equivalent to insertBack)
            result.arr[result.size++] = input.arr[i];
        }
    }

    return result;
}
ResidentArray searchByTransport(const ResidentArray& input, const string& mode) {
    ResidentArray result;

    // start small (like linked list growing)
    initResidentArray(result, 2);

    for (int i = 0; i < input.size; i++) {
        if (input.arr[i].modeOfTransport == mode) {

            // resize if full
            if (result.size == result.capacity) {
                int newCap = result.capacity * 2;

                Resident* newArr = new Resident[newCap];

                for (int j = 0; j < result.size; j++) {
                    newArr[j] = result.arr[j];
                }

                delete[] result.arr;
                result.arr = newArr;
                result.capacity = newCap;
            }

            // insert (same idea as insertBack)
            result.arr[result.size++] = input.arr[i];
        }
    }

    return result;
}

ResidentArray searchByDistance(const ResidentArray& input, double minDistance, double maxDistance) {
    ResidentArray result;

    // start small like a growing list
    initResidentArray(result, 2);

    for (int i = 0; i < input.size; i++) {
        if (input.arr[i].dailyDistance > minDistance && 
            input.arr[i].dailyDistance < maxDistance) {

            // resize if full
            if (result.size == result.capacity) {
                int newCap = result.capacity * 2;

                Resident* newArr = new Resident[newCap];

                for (int j = 0; j < result.size; j++) {
                    newArr[j] = result.arr[j];
                }

                delete[] result.arr;
                result.arr = newArr;
                result.capacity = newCap;
            }

            // insert (same pattern as insertBack)
            result.arr[result.size++] = input.arr[i];
        }
    }

    return result;
}

ResidentArray searchByEmission(const ResidentArray& input, double threshold) {
    ResidentArray result;

    // start small like dynamic growth
    initResidentArray(result, 2);

    for (int i = 0; i < input.size; i++) {
        if (input.arr[i].monthlyCarbonEmission > threshold) {

            // resize if full
            if (result.size == result.capacity) {
                int newCap = result.capacity * 2;

                Resident* newArr = new Resident[newCap];

                for (int j = 0; j < result.size; j++) {
                    newArr[j] = result.arr[j];
                }

				//Delete old array and update to new array and capacity
                delete[] result.arr;
                result.arr = newArr;
                result.capacity = newCap;
            }

            // insert
            result.arr[result.size++] = input.arr[i];
        }
    }

    return result;
}

void printResidentArray(const ResidentArray& arr) {
    const int n = arr.size;
    for (int i = 0; i < 10; i++) {
        const Resident& r = arr.arr[i];
        cout << left
            << setw(4) << i << "  "
            << setw(8) << r.ID
            << setw(6) << r.Age
            << setw(16) << r.modeOfTransport
            << setw(14) << fixed << setprecision(1) << r.dailyDistance
            << setw(20) << fixed << setprecision(2) << r.monthlyCarbonEmission
            << "\n";
    }
}