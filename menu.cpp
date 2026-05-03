#include "menu.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "RecordArrayUtils.hpp"
#include "ResidentArray.hpp"
#include "SortedArraySort.hpp"

using namespace std;

static void printSeparator(int width) {
    cout << string(width, '-') << "\n";
}

static void printTitle(const string& text, int width = 60) {
    const int padding = static_cast<int>(width - text.length()) / 2;
    cout << setfill('=') << setw(width) << "=" << "\n"
        << setfill(' ')
        << setw(padding + static_cast<int>(text.length())) << text << "\n"
        << setfill('=') << setw(width) << "=" << "\n";
}

static void printSubtitle(const string& text, int width = 60) {
    const int padding = static_cast<int>(width - text.length()) / 2;
    cout << "\n\n"
        << setfill('-') << setw(width) << "-" << "\n"
        << setfill(' ')
        << setw(padding + static_cast<int>(text.length())) << text << "\n"
        << setfill('-') << setw(width) << "-" << "\n";
}

static void displayProcessTime(chrono::duration<double, milli> ms) {
    cout << "\n  [Process time: " << fixed << setprecision(4) << ms.count() << " ms]\n";
}

static void waitToReturn() {
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    cout << "\n\n\n";
}

constexpr int kNumAgeGroups = 5;
const int kAgeMin[kNumAgeGroups] = { 6, 18, 26, 46, 61 };
const int kAgeMax[kNumAgeGroups] = { 17, 25, 45, 60, 100 };
const char* const kAgeLabel[kNumAgeGroups] = {
    "Children & Teenagers (6-17)",
    "University Students / Young Adults (18-25)",
    "Working Adults - Early Career (26-45)",
    "Working Adults - Late Career (46-60)",
    "Senior Citizens / Retirees (61-100)"
};

static const char* getSortName(int sortBy) {
    switch (sortBy) {
    case SORT_BY_AGE:
        return "Age";
    case SORT_BY_DISTANCE:
        return "Daily Distance";
    case SORT_BY_EMISSION:
        return "Monthly Carbon Emission";
    case SORT_BY_MODE:
        return "Mode of Transport";
    default:
        return "Unknown";
    }
}

static RecordArray* pickDataset(int ds, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    switch (ds) {
    case 1:
        return &cityA;
    case 2:
        return &cityB;
    case 3:
        return &cityC;
    case 4:
        return &combined;
    default:
        return nullptr;
    }
}

static const char* datasetLabel(int ds) {
    switch (ds) {
    case 1:
        return "City A - Metropolitan";
    case 2:
        return "City B - University Town";
    case 3:
        return "City C - Suburban/Rural";
    case 4:
        return "Combined A + B + C";
    default:
        return "";
    }
}

static void printMemoryEstimate(const RecordArray& records) {
    const int n = records.size;

    if (n <= 0 || records.arr == nullptr) {
        cout << "Memory estimate: 0 bytes\n";
        return;
    }

    size_t arrayBlock = static_cast<size_t>(n) * sizeof(Record);
    size_t stringHeap = 0;

    for (int i = 0; i < n; ++i) {
        stringHeap += records.arr[i].ID.capacity();
        stringHeap += records.arr[i].modeOfTransport.capacity();
    }

    size_t total = sizeof(RecordArray) + arrayBlock + stringHeap;

    cout << "Memory estimate: " << total << " bytes\n";
    cout << "  Struct array: " << arrayBlock << " bytes\n";
    cout << "  String heap: " << stringHeap << " bytes\n";
}

static void analyzeAllAgeGroupsRecords(const RecordArray& arr, const string& datasetName) {
    printSubtitle(datasetName);
    for (int g = 0; g < kNumAgeGroups; ++g) {
        int c = 0;
        for (int i = 0; i < arr.size; ++i) {
            const int a = arr.arr[i].Age;
            if (a >= kAgeMin[g] && a <= kAgeMax[g]) {
                ++c;
            }
        }
        cout << "  " << kAgeLabel[g] << ": " << c << "\n";
    }
}

static void runTimedSort(const RecordArray& original, int sortBy, const string& datasetName) {
    RecordArray work = copyRecordArray(original);

    auto start = chrono::high_resolution_clock::now();
    insertionSortArray(work, sortBy);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    cout << "\n";
    printSeparator(72);
    cout << "SORTED ARRAY - INSERTION SORT\n";
    cout << "Dataset : " << datasetName << "\n";
    cout << "Sort By : " << getSortName(sortBy) << "\n";
    printSeparator(72);

    cout << "Insertion sort time: " << fixed << setprecision(4) << elapsed.count() << " ms\n"
        << defaultfloat;

    cout << "Validation: " << (validateSorted(work, sortBy) ? "PASSED" : "FAILED") << "\n";

    cout << "\nFirst 10 records:\n";
    displayArrayPreview(work, 10);

    if (sortBy == SORT_BY_EMISSION) {
        cout << "\nLast 10 records:\n";
        displayLastNRecords(work, 10);
    }

    freeRecordArray(work);
}

static void runBinarySearchDemo(const RecordArray& original, const string& datasetName) {
    cout << "\n";
    printSeparator(72);
    cout << "SORTED ARRAY - BINARY SEARCH (results in ResidentArray)\n";
    cout << "Dataset : " << datasetName << "\n";
    printSeparator(72);

    ResidentArray matches{};
    initArray(matches);

    RecordArray byAge = copyRecordArray(original);
    insertionSortArray(byAge, SORT_BY_AGE);
    if (!validateSorted(byAge, SORT_BY_AGE)) {
        cout << "\nAge sort validation FAILED.\n";
        freeRecordArray(byAge);
        freeArray(matches);
        return;
    }

    cout << "\n--- Search by age (26-45) ---\n";
    auto ageStart = chrono::high_resolution_clock::now();
    const int nAge = binarySearchByAge(byAge, 26, 45, matches);
    auto ageEnd = chrono::high_resolution_clock::now();
    displayProcessTime(chrono::duration<double, milli>(ageEnd - ageStart));
    cout << "Matches: " << nAge << "\nFirst 10 results:\n";
    displayResidentArrayPreview(matches, 10);
    freeRecordArray(byAge);

    RecordArray byDistance = copyRecordArray(original);
    insertionSortArray(byDistance, SORT_BY_DISTANCE);
    if (!validateSorted(byDistance, SORT_BY_DISTANCE)) {
        cout << "\nDistance sort validation FAILED.\n";
        freeRecordArray(byDistance);
        freeArray(matches);
        return;
    }

    cout << "\n--- Search by daily distance (distance > 15 km) ---\n";
    auto dStart = chrono::high_resolution_clock::now();
    const int nDist = binarySearchByDistance(byDistance, 15.0, matches);
    auto dEnd = chrono::high_resolution_clock::now();
    displayProcessTime(chrono::duration<double, milli>(dEnd - dStart));
    cout << "Matches: " << nDist << "\nFirst 10 results:\n";
    displayResidentArrayPreview(matches, 10);
    freeRecordArray(byDistance);

    RecordArray byMode = copyRecordArray(original);
    insertionSortArray(byMode, SORT_BY_MODE);
    if (!validateSorted(byMode, SORT_BY_MODE)) {
        cout << "\nMode sort validation FAILED.\n";
        freeRecordArray(byMode);
        freeArray(matches);
        return;
    }

    cout << "\n--- Search by mode of transport ---\n";
    for (int m = 0; m < NUM_TRANSPORT_MODES; ++m) {
        cout << "  " << (m + 1) << ". " << TRANSPORT_MODE_NAMES[m] << "\n";
    }
    cout << "Enter mode number (1-" << NUM_TRANSPORT_MODES << "): ";
    int modeChoice = 0;
    cin >> modeChoice;

    if (modeChoice < 1 || modeChoice > NUM_TRANSPORT_MODES) {
        cout << "Invalid mode.\n";
    } else {
        const string modeStr(TRANSPORT_MODE_NAMES[modeChoice - 1]);
        auto mStart = chrono::high_resolution_clock::now();
        const int nMode = binarySearchByTransportMode(byMode, modeStr, matches);
        auto mEnd = chrono::high_resolution_clock::now();
        displayProcessTime(chrono::duration<double, milli>(mEnd - mStart));
        cout << "Mode: " << modeStr << "\nMatches: " << nMode << "\n";
        cout << "First 10 results:\n";
        displayResidentArrayPreview(matches, 10);
        cout << "Last 10 results:\n";
        displayResidentArrayLastN(matches, 10);
    }

    freeRecordArray(byMode);
    freeArray(matches);
}

static int selectAgeGroup() {
    int group;
    cout << "\nSelect age group:\n";
    for (int g = 0; g < kNumAgeGroups; ++g) {
        cout << "  " << (g + 1) << ". " << kAgeLabel[g] << "\n";
    }
    cout << "  0. Return\n"
        << "Enter choice: ";
    cin >> group;
    return group;
}

static int selectTransportModeUnified() {
    int mode;
    cout << "\nSelect transport mode:\n";
    for (int m = 0; m < NUM_TRANSPORT_MODES; ++m) {
        cout << "  " << (m + 1) << ". " << TRANSPORT_MODE_NAMES[m] << "\n";
    }
    cout << "  0. Return\n"
        << "Enter choice: ";
    cin >> mode;
    return mode;
}

static int selectDailyDistanceGroup() {
    int group;
    cout << "\nSelect daily distance band:\n"
        << "  1. 0-5 km\n"
        << "  2. 6-15 km\n"
        << "  3. 16+ km\n"
        << "  0. Return\n"
        << "Enter choice: ";
    cin >> group;
    return group;
}

static int selectDataSet() {
    int dataSet;
    cout << "\nSelect dataset:\n"
        << "  1. City A - Metropolitan\n"
        << "  2. City B - University Town\n"
        << "  3. City C - Suburban/Rural\n"
        << "  4. Combined A + B + C\n"
        << "  0. Return\n"
        << "Enter choice: ";
    cin >> dataSet;
    return dataSet;
}

static int selectDataContainer() {
    int container;
    cout << "\nSelect data container:\n"
        << "  1. Array (RecordArray + algorithms)\n"
        << "  2. Linked list (not implemented)\n"
        << "  0. Return\n"
        << "Enter choice: ";
    cin >> container;
    return container;
}

static int selectSortField() {
    int sortBy;
    cout << "\nSelect sorting field:\n"
        << "  1. Age\n"
        << "  2. Daily Distance\n"
        << "  3. Monthly Carbon Emission\n"
        << "  4. Mode of Transport\n"
        << "  0. Return\n"
        << "Enter choice: ";
    cin >> sortBy;
    return sortBy;
}

static void runArraySortingExperiment(
    RecordArray& cityA,
    RecordArray& cityB,
    RecordArray& cityC,
    RecordArray& combined,
    int dataSet,
    bool showResult
) {
    RecordArray* selected = pickDataset(dataSet, cityA, cityB, cityC, combined);

    if (selected == nullptr || selected->arr == nullptr || selected->size <= 0) {
        cout << "Invalid or empty dataset.\n";
        return;
    }

    const int sortBy = selectSortField();

    if (sortBy == 0) {
        cout << "Returning.\n";
        return;
    }

    if (sortBy != SORT_BY_AGE && sortBy != SORT_BY_DISTANCE && sortBy != SORT_BY_EMISSION && sortBy != SORT_BY_MODE) {
        cout << "Invalid sorting field.\n";
        return;
    }

    if (!showResult) {
        RecordArray work = copyRecordArray(*selected);
        auto start = chrono::high_resolution_clock::now();
        insertionSortArray(work, sortBy);
        auto end = chrono::high_resolution_clock::now();
        cout << "\nSorted " << selected->size << " records.\n";
        displayProcessTime(chrono::duration<double, milli>(end - start));
        cout << "Validation: " << (validateSorted(work, sortBy) ? "PASSED" : "FAILED") << "\n";
        freeRecordArray(work);
        return;
    }

    runTimedSort(*selected, sortBy, datasetLabel(dataSet));
}

static void runArrayAgeSearch(
    RecordArray& cityA,
    RecordArray& cityB,
    RecordArray& cityC,
    RecordArray& combined,
    int dataSet,
    int ageGroup,
    bool showResult
) {
    if (ageGroup < 1 || ageGroup > kNumAgeGroups) {
        cout << "Invalid age group.\n";
        return;
    }

    RecordArray* selected = pickDataset(dataSet, cityA, cityB, cityC, combined);
    if (selected == nullptr || selected->size <= 0) {
        cout << "Invalid or empty dataset.\n";
        return;
    }

    const int g = ageGroup - 1;
    const int minAge = kAgeMin[g];
    const int maxAge = kAgeMax[g];

    RecordArray sorted = copyRecordArray(*selected);
    insertionSortArray(sorted, SORT_BY_AGE);
    if (!validateSorted(sorted, SORT_BY_AGE)) {
        cout << "Sort validation FAILED.\n";
        freeRecordArray(sorted);
        return;
    }

    ResidentArray matches{};
    initArray(matches);

    auto start = chrono::high_resolution_clock::now();
    const int n = binarySearchByAge(sorted, minAge, maxAge, matches);
    auto end = chrono::high_resolution_clock::now();

    cout << "\nAge search: " << kAgeLabel[g] << " (" << minAge << "-" << maxAge << ")\n";
    cout << "Matches: " << n << "\n";
    if (showResult) {
        displayProcessTime(chrono::duration<double, milli>(end - start));
        cout << "First 15 results:\n";
        displayResidentArrayPreview(matches, 15);
    }

    freeRecordArray(sorted);
    freeArray(matches);
}

static void runArrayTransportSearch(
    RecordArray& cityA,
    RecordArray& cityB,
    RecordArray& cityC,
    RecordArray& combined,
    int dataSet,
    int modeChoice,
    bool showResult
) {
    if (modeChoice < 1 || modeChoice > NUM_TRANSPORT_MODES) {
        cout << "Invalid mode.\n";
        return;
    }

    RecordArray* selected = pickDataset(dataSet, cityA, cityB, cityC, combined);
    if (selected == nullptr || selected->size <= 0) {
        cout << "Invalid or empty dataset.\n";
        return;
    }

    const string modeStr(TRANSPORT_MODE_NAMES[modeChoice - 1]);

    RecordArray sorted = copyRecordArray(*selected);
    insertionSortArray(sorted, SORT_BY_MODE);
    if (!validateSorted(sorted, SORT_BY_MODE)) {
        cout << "Sort validation FAILED.\n";
        freeRecordArray(sorted);
        return;
    }

    ResidentArray matches{};
    initArray(matches);

    auto start = chrono::high_resolution_clock::now();
    const int n = binarySearchByTransportMode(sorted, modeStr, matches);
    auto end = chrono::high_resolution_clock::now();

    cout << "\nTransport search: " << modeStr << "\nMatches: " << n << "\n";
    if (showResult) {
        displayProcessTime(chrono::duration<double, milli>(end - start));
        cout << "First 15 results:\n";
        displayResidentArrayPreview(matches, 15);
    }

    freeRecordArray(sorted);
    freeArray(matches);
}

static void runArrayDistanceBandSearch(
    RecordArray& cityA,
    RecordArray& cityB,
    RecordArray& cityC,
    RecordArray& combined,
    int dataSet,
    int dGroup,
    bool showResult
) {
    double minKm = 0.0;
    double maxKm = 0.0;
    const char* label = "";

    switch (dGroup) {
    case 1:
        minKm = 0.0;
        maxKm = 5.0;
        label = "0-5 km";
        break;
    case 2:
        minKm = 6.0;
        maxKm = 15.0;
        label = "6-15 km";
        break;
    case 3:
        minKm = 16.0;
        maxKm = numeric_limits<double>::max();
        label = "16+ km";
        break;
    default:
        cout << "Invalid distance group.\n";
        return;
    }

    RecordArray* selected = pickDataset(dataSet, cityA, cityB, cityC, combined);
    if (selected == nullptr || selected->size <= 0) {
        cout << "Invalid or empty dataset.\n";
        return;
    }

    RecordArray sorted = copyRecordArray(*selected);
    insertionSortArray(sorted, SORT_BY_DISTANCE);
    if (!validateSorted(sorted, SORT_BY_DISTANCE)) {
        cout << "Sort validation FAILED.\n";
        freeRecordArray(sorted);
        return;
    }

    ResidentArray matches{};
    initArray(matches);

    auto start = chrono::high_resolution_clock::now();
    const int n = searchByDailyDistanceRange(sorted, minKm, maxKm, matches);
    auto end = chrono::high_resolution_clock::now();

    cout << "\nDistance band: " << label << "\nMatches: " << n << "\n";
    if (showResult) {
        displayProcessTime(chrono::duration<double, milli>(end - start));
        cout << "First 15 results:\n";
        displayResidentArrayPreview(matches, 15);
    }

    freeRecordArray(sorted);
    freeArray(matches);
}

static void searchingCriteriaMenu(
    int container,
    int dataSet,
    bool showResult,
    RecordArray& cityA,
    RecordArray& cityB,
    RecordArray& cityC,
    RecordArray& combined
) {
    if (container == 2) {
        cout << "Linked-list search is not implemented in this build.\n";
        return;
    }

    int nav;
    cout << "\nSelect search type:\n"
        << "  1. Search by age group\n"
        << "  2. Search by mode of transport\n"
        << "  3. Search by daily distance band\n"
        << "  0. Return\n"
        << "Enter choice: ";
    cin >> nav;

    if (nav == 0) {
        return;
    }

    switch (nav) {
    case 1: {
        const int aGroup = selectAgeGroup();
        if (aGroup == 0) {
            return;
        }
        runArrayAgeSearch(cityA, cityB, cityC, combined, dataSet, aGroup, showResult);
        break;
    }
    case 2: {
        const int mode = selectTransportModeUnified();
        if (mode == 0) {
            return;
        }
        runArrayTransportSearch(cityA, cityB, cityC, combined, dataSet, mode, showResult);
        break;
    }
    case 3: {
        const int dGroup = selectDailyDistanceGroup();
        if (dGroup == 0) {
            return;
        }
        runArrayDistanceBandSearch(cityA, cityB, cityC, combined, dataSet, dGroup, showResult);
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

static void emissionMenu() {
    int nav;
    while (true) {
        printSubtitle("Carbon Emission Analysis");
        cout << "Select option:\n"
            << "  1. Compare by age group (record counts)\n"
            << "  2. Placeholder - mode comparison\n"
            << "  3. Placeholder - distance comparison\n"
            << "  0. Return\n"
            << "Enter choice: ";
        cin >> nav;
        switch (nav) {
        case 1:
            cout << "Use main menu item 1 for per-city age breakdown, or extend here.\n";
            waitToReturn();
            return;
        case 2:
        case 3:
            cout << "Not implemented yet.\n";
            waitToReturn();
            return;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

static void sortingMenu(bool display, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    while (true) {
        printSubtitle("Sorting Experiment");
        int nav;
        cout << "Select container:\n"
            << "  1. Array\n"
            << "  2. Linked list (not implemented)\n"
            << "  0. Return\n"
            << "Enter choice: ";
        cin >> nav;

        if (nav == 0) {
            return;
        }
        if (nav == 2) {
            cout << "Linked list sorting is not implemented.\n";
            waitToReturn();
            continue;
        }
        if (nav != 1) {
            cout << "Invalid choice.\n";
            continue;
        }

        const int dataSet = selectDataSet();
        if (dataSet == 0) {
            return;
        }
        if (dataSet < 1 || dataSet > 4) {
            cout << "Invalid dataset.\n";
            continue;
        }

        runArraySortingExperiment(cityA, cityB, cityC, combined, dataSet, display);
        waitToReturn();
        return;
    }
}

static void searchingMenu(bool display, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    while (true) {
        printSubtitle("Searching Experiment");
        const int container = selectDataContainer();
        if (container == 0) {
            return;
        }

        const int dataSet = selectDataSet();
        if (dataSet == 0) {
            return;
        }
        if (dataSet < 1 || dataSet > 4) {
            cout << "Invalid dataset.\n";
            continue;
        }

        searchingCriteriaMenu(container, dataSet, display, cityA, cityB, cityC, combined);
        waitToReturn();
        return;
    }
}

static void sortedArrayToolsMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    while (true) {
        printSubtitle("Sorted Array Tools (CSV datasets)");
        int choice;
        cout << "  1. Memory estimate\n"
            << "  2. Insertion sort experiment\n"
            << "  3. Binary search demo (age / distance / mode)\n"
            << "  4. Show original first 10 records\n"
            << "  0. Return\n"
            << "Enter choice: ";
        cin >> choice;

        if (choice == 0) {
            return;
        }

        const int ds = (choice >= 1 && choice <= 4) ? selectDataSet() : 0;
        if (choice != 0 && ds == 0) {
            continue;
        }
        if (ds < 0 || ds > 4) {
            cout << "Invalid dataset.\n";
            continue;
        }

        RecordArray* selected = pickDataset(ds, cityA, cityB, cityC, combined);
        if (selected == nullptr || selected->size <= 0) {
            cout << "Invalid or empty dataset.\n";
            continue;
        }

        if (choice == 1) {
            cout << "\nDataset: " << datasetLabel(ds) << "\n";
            printMemoryEstimate(*selected);
        } else if (choice == 2) {
            const int sortBy = selectSortField();
            if (sortBy == 0) {
                continue;
            }
            if (sortBy != SORT_BY_AGE && sortBy != SORT_BY_DISTANCE && sortBy != SORT_BY_EMISSION && sortBy != SORT_BY_MODE) {
                cout << "Invalid sort field.\n";
                continue;
            }
            runTimedSort(*selected, sortBy, datasetLabel(ds));
        } else if (choice == 3) {
            runBinarySearchDemo(*selected, datasetLabel(ds));
        } else if (choice == 4) {
            cout << "\nFirst 10 records - " << datasetLabel(ds) << "\n";
            displayArrayPreview(*selected, 10);
        } else {
            cout << "Invalid option.\n";
        }

        waitToReturn();
    }
}

static void resultMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    while (true) {
        printSubtitle("Experiment Results");
        int nav;
        cout << "  1. Sorting (timing only)\n"
            << "  2. Searching (timing only)\n"
            << "  0. Return\n"
            << "Enter choice: ";
        cin >> nav;
        switch (nav) {
        case 1:
            sortingMenu(false, cityA, cityB, cityC, combined);
            break;
        case 2:
            searchingMenu(false, cityA, cityB, cityC, combined);
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void MainMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
    int nav;
    while (true) {
        printTitle("Main Menu");
        cout << "  1. Age group summary (all cities)\n"
            << "  2. Carbon emission menu\n"
            << "  3. Sorting experiment\n"
            << "  4. Searching experiment\n"
            << "  5. Experiment results (quiet)\n"
            << "  6. Sorted array tools (memory / sort / binary demo)\n"
            << "  0. Exit\n"
            << "Enter choice: ";
        cin >> nav;

        switch (nav) {
        case 1:
            analyzeAllAgeGroupsRecords(cityA, "City A - Metropolitan");
            analyzeAllAgeGroupsRecords(cityB, "City B - University Town");
            analyzeAllAgeGroupsRecords(cityC, "City C - Suburban/Rural");
            waitToReturn();
            break;
        case 2:
            emissionMenu();
            break;
        case 3:
            sortingMenu(true, cityA, cityB, cityC, combined);
            waitToReturn();
            break;
        case 4:
            searchingMenu(true, cityA, cityB, cityC, combined);
            waitToReturn();
            break;
        case 5:
            resultMenu(cityA, cityB, cityC, combined);
            break;
        case 6:
            sortedArrayToolsMenu(cityA, cityB, cityC, combined);
            break;
        case 0:
            cout << "Goodbye.\n";
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
