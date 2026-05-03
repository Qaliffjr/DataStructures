/*#define _HAS_STD_BYTE 0

#include "ResidentArray.hpp"
#include "dataStore.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
using namespace std;

int arrayMain() {
    auto programStart = chrono::high_resolution_clock::now();

    printSeparator(72);
    cout << "  CITYVILLE CARBON EMISSION ANALYSIS  (Array - Unsorted)\n";
    cout << "  Tasks: 4 (Age Group Analysis) & 7 (Searching)\n";
    printSeparator(72);

    // --------------------------------------------------------
    //  Menu
    // --------------------------------------------------------
    int choice;
    do {
        cout << "\n";
        printSeparator(72);
        cout << "  MAIN MENU\n";
        printSeparator(72);
        cout << "  --- TASK 4: Age Group Analysis ---\n";
        cout << "  1. Analyse City A (Metropolitan)\n";
        cout << "  2. Analyse City B (University Town)\n";
        cout << "  3. Analyse City C (Suburban/Rural)\n";
        cout << "\n  --- TASK 7: Search ---\n";
        cout << "  4. Search by Age Group\n";
        cout << "  5. Search by Transport Mode\n";
        cout << "  6. Search by Daily Distance Threshold\n";
        cout << "\n  0. Exit\n";
        printSeparator(72);
        cout << "  Enter choice: ";
        cin >> choice;

        auto opStart = chrono::high_resolution_clock::now();

        // ---- Task 4 ----
        if (choice == 1) {
            analyzeAllAgeGroups(arr1.arr, arr1.size, "City A - Metropolitan");
        }
        else if (choice == 2) {
            analyzeAllAgeGroups(arr2.arr, arr2.size, "City B - University Town");
        }
        else if (choice == 3) {
            analyzeAllAgeGroups(arr3.arr, arr3.size, "City C - Suburban/Rural");
        }

        // ---- Task 7 ----
        else if (choice == 4) {
            cout << "\n  Which dataset?\n";
            cout << "  1. City A    2. City B    3. City C\n";
            cout << "  Choice: ";
            int ds; cin >> ds;

            cout << "\n  Age Groups:\n";
            for (int g = 0; g < NUM_AGE_GROUPS; g++)
                cout << "  " << g << ". " << AGE_LABEL[g] << "\n";
            cout << "  Enter group number (0-4): ";
            int g; cin >> g;

            if (ds == 1) searchByAgeGroup(arr1.arr, arr1.size, g);
            else if (ds == 2) searchByAgeGroup(arr2.arr, arr2.size, g);
            else if (ds == 3) searchByAgeGroup(arr3.arr, arr3.size, g);
            else cout << "[ERROR] Invalid dataset.\n";
        }
        else if (choice == 5) {
            cout << "\n  Which dataset?\n";
            cout << "  1. City A    2. City B    3. City C\n";
            cout << "  Choice: ";
            int ds; cin >> ds;

            cout << "\n  Transport Modes:\n";
            for (int m = 0; m < NUM_MODES; m++)
                cout << "  " << m + 1 << ". " << MODES[m] << "\n";
            cout << "  Enter mode number (1-" << NUM_MODES << "): ";
            int m; cin >> m;

            if (m < 1 || m > NUM_MODES) {
                cout << "[ERROR] Invalid mode.\n";
            }
            else {
                if (ds == 1) searchByTransport(arr1.arr, arr1.size, MODES[m - 1]);
                else if (ds == 2) searchByTransport(arr2.arr, arr2.size, MODES[m - 1]);
                else if (ds == 3) searchByTransport(arr3.arr, arr3.size, MODES[m - 1]);
                else cout << "[ERROR] Invalid dataset.\n";
            }
        }
        else if (choice == 6) {
            cout << "\n  Which dataset?\n";
            cout << "  1. City A    2. City B    3. City C\n";
            cout << "  Choice: ";
            int ds; cin >> ds;

            cout << "  Enter distance threshold (km): ";
            double threshold; cin >> threshold;

            if (ds == 1) searchByDistance(arr1.arr, arr1.size, threshold);
            else if (ds == 2) searchByDistance(arr2.arr, arr2.size, threshold);
            else if (ds == 3) searchByDistance(arr3.arr, arr3.size, threshold);
            else cout << "[ERROR] Invalid dataset.\n";
        }
        else if (choice != 0) {
            cout << "[ERROR] Invalid option.\n";
        }

        // Per-operation time
        if (choice != 0) {
            auto opEnd = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> ms = opEnd - opStart;
            cout << "\n  [Operation time: " << fixed << setprecision(4)
                << ms.count() << " ms]\n";
        }

    } while (choice != 0);

    // --------------------------------------------------------
    //  Execution time summary (no memory - not needed)
    // --------------------------------------------------------
    auto programEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = programEnd - programStart;

    cout << "\n";
    printSeparator(72);
    cout << "  PERFORMANCE SUMMARY\n";
    printSeparator(72);
    cout << "  Total execution time : " << fixed << setprecision(4)
        << elapsed.count() << " seconds\n";
    cout << "  Total records loaded : " << arr1.size + arr2.size + arr3.size << "\n";
    printSeparator(72);
    cout << "\n";

    return 0;
}
*/