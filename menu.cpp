#include "menu.hpp"
#include "ResidentArray.hpp"
#include "ResidentLinkedList.hpp"
#include "ResidentArrayUtils.hpp"
#include "tableDisplay.hpp"
#include "dataStore.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;


//==================================================================
//==================================================================
//==================================================================
//Helper Functions for Menus

//Get Input and Clear Buffer
void getInput(int& input) {
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Prints
void printTitle(string text, int width = 60) {
    int padding = (width - text.length()) / 2;
    cout << setfill('=') << setw(width) << "=" << "\n"
        << setfill(' ') << setw(padding + text.length()) << text << "\n"
        << setfill('=') << setw(width) << "=" << "\n";
}

void printSubtitle(string text, int width = 60) {
    int padding = (width - text.length()) / 2;
    cout << "\n\n"
        << setfill('-') << setw(width) << "-" << "\n"
        << setfill(' ') << setw(padding + text.length()) << text << "\n"
        << setfill('-') << setw(width) << "-" << "\n";
}

void displayProcessTime(chrono::duration<double, milli> ms) {
    cout << "\n  [Process time: " << fixed << setprecision(4) << ms.count() << " ms]\n";
}

void waitToReturn() {
    cout << "Press Enter to return to the main menu...";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear leftover
    cin.get();

    cout << "\n\n\n";
}

//Get Dataset
ResidentArray& getArrayByDataset(int dataSet) {
    if (dataSet == 1) return arr1;
    if (dataSet == 2) return arr2;
    if (dataSet == 3) return arr3;
    return arrCombined;
}

ResidentLinkedList& getListByDataset(int dataSet) {
    if (dataSet == 1) return list1;
    if (dataSet == 2) return list2;
    if (dataSet == 3) return list3;
    return listCombined;
}


//Extra Logic for Criterias

int getMinAge(int group) {
    if (group == 1) return 6;
    if (group == 2) return 18;
    if (group == 3) return 26;
    if (group == 4) return 46;
    if (group == 5) return 61;
    return 0;
}

int getMaxAge(int group) {
    if (group == 1) return 17;
    if (group == 2) return 25;
    if (group == 3) return 45;
    if (group == 4) return 60;
    if (group == 5) return 100;
    return 100;
}

int getMinDistance(int group) {
    if (group == 1) return 0;
    if (group == 2) return 6;
    if (group == 3) return 16;
    return 0;
}

int getMaxDistance(int group) {
    if (group == 1) return 5;
    if (group == 2) return 15;
    if (group == 3) return 100;
    return 100;
}


//==================================================================
//==================================================================
//==================================================================
//Run Searches
//===== Age Group =====
ResidentArray runSearchAgeUnsortedArray(int dataSet, int group) {
    return searchByAgeGroup(getArrayByDataset(dataSet), group);
}

//ResidentArray runSearchAgeSortedArray(int dataSet, int group) {
//    int min = getMinAge(group);
//    int max = getMaxAge(group);
//    //Emal
//}

ResidentLinkedList runSearchAgeUnsortedList(int dataSet, int group) {
    int min = getMinAge(group);
    int max = getMaxAge(group);
    return linearSearchListByAge(getListByDataset(dataSet), min, max);
}

//ResidentLinkedList runSearchAgeSortedList(int dataset, int group) {
//    //Gaku
//}

//===== Transport Mode =====
ResidentArray runSearchTransportUnsortedArray(int dataSet, const string& mode) {
    return searchByTransport(getArrayByDataset(dataSet), mode);
}

//ResidentArray runSearchTransportSortedArray(int dataSet, const string& mode) {
//    //Emal
//}

ResidentLinkedList runSearchTransportUnsortedList(int dataSet, const string& mode) {
    return linearSearchListByTransport(getListByDataset(dataSet), mode);
}

//ResidentLinkedList runSearchTransportSortedList(int dataSet, const string& mode) {
//    //Gaku
//}

//Distance Traveled
ResidentArray runSearchDistanceUnsortedArray(int dataSet, int group) {
    int min = getMinDistance(group);
    int max = getMaxDistance(group);
    return searchByDistance(getArrayByDataset(dataSet), min, max);
}
//ResidentArray runSearchDistanceSortedArray(int dataSet, double threshold) {
//    //Emal
//}

ResidentLinkedList runSearchDistanceUnsortedList(int dataSet, int group) {
    int min = getMinDistance(group);
    int max = getMaxDistance(group);
    return linearSearchListByDailyDistance(getListByDataset(dataSet), min, max);
}

//ResidentLinkedList runSearchDistanceSortedList(int dataSet, int group) {
//    //Gaku
//}

//Monthly Emission
ResidentArray runSearchEmissionUnsortedArray(int dataSet, double threshold) {
    return searchByEmission(getArrayByDataset(dataSet), threshold);
}

//ResidentArray runSearchEmissionSortedArray(int dataSet, double threshold) {
//    //Emal
//}

ResidentLinkedList runSearchEmissionUnsortedList(int dataSet, double threshold) {
    return linearSearchListByEmission(getListByDataset(dataSet), threshold);
}

//ResidentLinkedList runSearchEmissionSortedList(int dataSet, double threshold) {
//    //Gaku
//}


//==================================================================
//==================================================================
//==================================================================
//Selection Menus

int selectAgeGroup() {
    int group;
    cout << "\nPlease select an age group from the menu below:\n"
        << "1. Children & Teenagers (6-17)\n"
        << "2. University Students / Young Adults (18-25)\n"
        << "3. Working Adults - Early Career (26-45)\n"
        << "4. Working Adults - Late Career (46-60)\n"
        << "5. Senior Citizens / Retirees (61-100)\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(group);
    return group;
}

int selectTransportMode1() {
    int mode;
    cout << "\nPlease select a mode of transport from the menu below:\n"
        << "1. Car\n"
        << "2. Bus\n"
        << "3. Bicycle\n"
        << "4. Walking\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(mode);
    return mode;
}

int selectTransportMode2() {
    int mode;
    cout << "\nPlease select a mode of transport from the menu below:\n"
        << "1. Carpool\n"
        << "2. School Bus\n"
        << "3. Bicycle\n"
        << "4. Walking\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(mode);
    return mode;
}

int selectTransportMode3() {
    int mode;
    cout << "\nPlease select a mode of transport from the menu below:\n"
        << "1. Car\n"
        << "2. Carpool\n"
        << "3. Bicyle\n"
        << "4. Bus\n"
        << "5. School Bus\n"
        << "6. Walking\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(mode);
    return mode;
}

int selectDailyDistanceGroup() {
    int group;
    cout << "Please select a daily distance traveled group from the menu below:\n"
        << "1. 0-5 km\n"
        << "2. 6-15 km\n"
        << "3. 16+ km\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(group);
    return group;
}

int selectDataSet() {
    int dataSet;
    cout << "Please select a dataset from the menu below:\n"
        << "1. City A - Metropolitan\n"
        << "2. City B - University Town\n"
        << "3. City C - Suburban/Rural\n"
		<< "4. All Datasets\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
	getInput(dataSet);
    return dataSet;
}

int selectDataContainer() {
    int container;
    cout << "Please select a data container from the menu below:\n"
        << "1. Array\n"
        << "2. Linked List\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(container);
    return container;
}

int selectSorted() {
    int sorted;
    cout << "Please select whether the data sorting:\n"
        << "1. Unsorted\n"
        << "2. Sorted\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    getInput(sorted);
    return sorted;
}


//==================================================================
//==================================================================
//==================================================================
//Level 2 Menus


void SearchingCriteriaMenu(int container, int dataSet, bool showResult, bool sorted) {

    int nav;

    cout << "Please select a searching criteria from the menu below:\n"
        << "1. Search by Age Group\n"
        << "2. Search by Mode of Transport\n"
        << "3. Search by Daily Distance Traveled\n"
        << "4. Search by Minimum Monthly Emission\n"
        << "0. Exit\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";

    getInput(nav);

    if (nav == 0) {
        cout << "Returning to previous page.\n";
        return;
    }

    ResidentArray arrResult;
    ResidentLinkedList listResult;

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed;
    if (showResult) {
        //Do 1 Specific Algo, Then display result at the end

        switch (nav) {

                // =========================
                // AGE GROUP
            case 1: {
                int group = selectAgeGroup();
                if (group == 0) return;
                if (sorted) {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        //arrResult = runSearchAgeSortedArray(dataSet, group);
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        //listResult = runSearchAgeSortedList(dataSet, group);
                    }
                }
                else {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        arrResult = runSearchAgeUnsortedArray(dataSet, group);
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        listResult = runSearchAgeUnsortedList(dataSet, group);
                    }
                }
                break;
            }

                  // =========================
                  // TRANSPORT
            case 2: {
                int mode;

                if (dataSet == 1) mode = selectTransportMode1();
                else if (dataSet == 2) mode = selectTransportMode2();
                else mode = selectTransportMode3();
                if (mode == 0) return;

                string modeStr = MODES[mode - 1];
                if (sorted) {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        //arrResult = runSearchTransportSortedArray(dataSet, modeStr);
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        //listResult = runSearchTransportSortedList(dataSet, modeStr);
                    }
                }
                else {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        arrResult = runSearchTransportUnsortedArray(dataSet, modeStr);
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        listResult = runSearchTransportUnsortedList(dataSet, modeStr);
                    }
                }
                break;
            }

                  // =========================
                  // DISTANCE
            case 3: {
                int group = selectDailyDistanceGroup();
                if (group == 0) return;

                if (sorted) {
                    if (container == 1) {
                        //arrResult = runSearchDistanceSortedArray(dataSet, group);
                    }
                    else {
                        //listResult = runSearchDistanceSortedList(dataSet, group);
                    }

                }
                else {
                    if (container == 1) {
                        arrResult = runSearchDistanceUnsortedArray(dataSet, group);
                    }
                    else {
                        listResult = runSearchDistanceUnsortedList(dataSet, group);
                    }
                }
                break;
            }

                  // =========================
                  // EMISSION
            case 4: {
                int threshold;

                cout << "Enter minimum monthly emission: ";
                getInput(threshold);
            
                if (sorted) {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        //arrResult = runSearchEmissionSortedArray(dataSet, threshold); // sorted (binary search)
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        //listResult = runSearchEmissionSortedList(dataSet, threshold); // linear
                    }
                }
                else {
                    if (container == 1) {
                        start = chrono::high_resolution_clock::now();
                        arrResult = runSearchEmissionUnsortedArray(dataSet, threshold);
                    }
                    else {
                        start = chrono::high_resolution_clock::now();
                        listResult = runSearchEmissionUnsortedList(dataSet, threshold);
                    }
                }
                break;
            }
        }
        // =========================
        // DISPLAY SEARCH RESULTS
        if (container == 1) {
            printResidentArray(arrResult);
            freeResidentArray(arrResult);
        }
        else {
            printResidentLinkedList(listResult);
            freeResidentLinkedList(listResult);
        }

        end = chrono::high_resolution_clock::now();
        elapsed = end - start;
        displayProcessTime(elapsed);
    }

    else {
        //Do All Algo, But count process time individually

        //Prepare Table
        const int COLS = 3;

        std::string headers[COLS] = {
            "Algorithm",
            "Time Used",
            "Memory Used"
        };

        int widths[COLS] = {
        50,  // Algorithm Name
        30,  // Time Used (in ms)
        30,  // Memory Used (in bytes)
        };

        std::string rows[5][10];
        int rowCount = 4;
        rows[0][0] = "[Unsorted Searching Algorithm] - Array";
        rows[1][0] = "[Sorted Searching Algorithm] - Array";
        rows[2][0] = "[Unsorted Searching Algorithm] - Linked List";
        rows[3][0] = "[Sorted Searching Algorithm] - Linked List";

        //RUN ALGO, Calculate Time, Store runtime, store memoryused, drop data
        switch (nav) {

            // =========================
            // AGE GROUP
        case 1: {
            int group = selectAgeGroup();
            if (group == 0) return;
            
            //RUN UNSORTED ARRAY
            start = chrono::high_resolution_clock::now();
            arrResult = runSearchAgeUnsortedArray(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[0][1] = to_string(elapsed.count());
            // rows[0][2] = Memory

            //RUN SORTED ARRAY
            start = chrono::high_resolution_clock::now();
            //arrResult = runSearchAgeSortedArray(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[1][1] = to_string(elapsed.count());
            // rows[1][2] = Memory


            //RUN UNSORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            listResult = runSearchAgeUnsortedList(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[2][1] = to_string(elapsed.count());
            // rows[2][2] = Memory

            //RUN SORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            //listResult = runSearchAgeSortedList(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[3][1] = to_string(elapsed.count());
            // rows[3][2] = Memory



            string text = AGE_LABEL[group];
            printSubtitle("Searching Experiment Results - Age Group (" + text + ")");
            break;
        }

              // =========================
              // TRANSPORT
        case 2: {
            int mode;

            if (dataSet == 1) mode = selectTransportMode1();
            else if (dataSet == 2) mode = selectTransportMode2();
            else mode = selectTransportMode3();
            if (mode == 0) return;

            string modeStr = MODES[mode - 1];

            //RUN UNSORTED ARRAY
            start = chrono::high_resolution_clock::now();
            arrResult = runSearchTransportUnsortedArray(dataSet, modeStr);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[0][1] = to_string(elapsed.count());
            // rows[0][2] = Memory

            //RUN SORTED ARRAY
            start = chrono::high_resolution_clock::now();
            //arrResult = runSearchTransportSortedArray(dataSet, modeStr);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[1][1] = to_string(elapsed.count());
            // rows[1][2] = Memory


            //RUN UNSORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            listResult = runSearchTransportUnsortedList(dataSet, modeStr);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[2][1] = to_string(elapsed.count());
            // rows[2][2] = Memory

            //RUN SORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            //listResult = runSearchTransportSortedList(dataSet, modeStr);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[3][1] = to_string(elapsed.count());
            // rows[3][2] = Memory


            printSubtitle("Searching Experiment Results - Mode of Transport (" + modeStr + ")");
            break;
        }

              // =========================
              // DISTANCE
        case 3: {
            int group = selectDailyDistanceGroup();
            if (group == 0) return;

            //RUN UNSORTED ARRAY
            start = chrono::high_resolution_clock::now();
            arrResult = runSearchDistanceUnsortedArray(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[0][1] = to_string(elapsed.count());
            // rows[0][2] = Memory

            //RUN SORTED ARRAY
            start = chrono::high_resolution_clock::now();
            //arrResult = runSearchDistanceSortedArray(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[1][1] = to_string(elapsed.count());
            // rows[1][2] = Memory


            //RUN UNSORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            listResult = runSearchDistanceUnsortedList(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[2][1] = to_string(elapsed.count());
            // rows[2][2] = Memory

            //RUN SORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            //listResult = runSearchDistanceSortedList(dataSet, group);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[3][1] = to_string(elapsed.count());
            // rows[3][2] = Memory

            string text;
            if (group == 1) text = "<5 km";
            else if (group == 2) text = "6-15 km";
            else if (group == 3) text = ">15 km";
            printSubtitle("Searching Experiment Results - Daily Distance (" + text + ")");
            
            break;
        }

              // =========================
              // EMISSION
        case 4: {
            int threshold;

            cout << "Enter minimum monthly emission: ";
            getInput(threshold);


            //RUN UNSORTED ARRAY
            start = chrono::high_resolution_clock::now();
            arrResult = runSearchEmissionUnsortedArray(dataSet, threshold);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[0][1] = to_string(elapsed.count());
            // rows[0][2] = Memory

            //RUN SORTED ARRAY
            start = chrono::high_resolution_clock::now();
            //arrResult = runSearchEmissionSortedArray(dataSet, threshold);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[1][1] = to_string(elapsed.count());
            // rows[1][2] = Memory


            //RUN UNSORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            listResult = runSearchEmissionUnsortedList(dataSet, threshold);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count Memory
            rows[2][1] = to_string(elapsed.count());
            // rows[2][2] = Memory

            //RUN SORTED LINKED LIST
            start = chrono::high_resolution_clock::now();
            //listResult = runSearchEmissionSortedList(dataSet, threshold);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            //Count memory
            rows[3][1] = to_string(elapsed.count());
            // rows[3][2] = Memory


            printSubtitle("Searching Experiment Results - Minimum Emission (" + to_string(threshold) + " kg CO2)");
            break;
        }
        }
        
        // =========================
        // DISPLAY EXPERIMENT RESULTS
        printTable(headers, COLS, rows, rowCount, widths);
    }
}


//==================================================================
//==================================================================
//Level 1 Menus
void EmissionMenu() {
    int nav;
    while (true) {
		printSubtitle("Carbon Emission Analysis");
        cout << "Please select an option from the menu below:\n"
            << "1. Compare Carbon Emissions by Dataset\n"
            << "2. Compare Carbon Emissions by Mode of Transport\n"
            << "3. Compare Carbon Emissions by Age Group\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        getInput(nav);
        switch (nav) {
        case 1:
			analyzeEmissionByDataset(list1, list2, list3);
            // Call Function to Compare Carbon Emissions by Dataset & Display Results
            waitToReturn();
            return;
        case 2:
            analyzeEmissionByMode(list1, list2, list3);
            // Call Function to Compare Carbon Emissions by Mode of Transport & Display Results
            waitToReturn();
            return;
        case 3:
            analyzeEmissionByAgeGroup(list1, list2, list3);
            // Call Function to Compare Carbon Emissions by Age Group & Display Results
            waitToReturn();
            return;
        case 0:
            cout << "Returning to previous page.\n";
            return;
        default:
            cout << "Invalid choice. Please select a valid option from the menu.\n";
        }
    }
}


void SortingMenu(bool display) {
    int nav;
    while (true) {
        //Select Array/Linked List for Sorting Experiment
		printSubtitle("Sorting Experiment");
        cout << "Please Select Data Container:\n"
            << "1. Array\n"
            << "2. Linked List\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        getInput(nav);

        if (nav == 0) {
            cout << "Returning to Menu...\n";
            return;
        }

        //Select Data Set for Sorting Experiment
        int dataSet;
        cout << "\nPlease select the dataset to sort:\n"
            << "1. DataSet 1\n"
            << "2. DataSet 2\n"
            << "3. DataSet 3\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        cin >> dataSet;

        if (dataSet == 0) {
            cout << "Returning to Menu...\n";
            return;
        }
        else {
            switch (dataSet) {
            case 1:
                if (nav == 1) {
                    // Call Sorting Experiment Function for Array with DataSet 1
                    waitToReturn();
                }
                else if (nav == 2) {
                    // Call Sorting Experiment Function for Linked List with DataSet 1
                    waitToReturn();
                }
                return;
            case 2:
                if (nav == 1) {
                    // Call Sorting Experiment Function for Array with DataSet 1
                    waitToReturn();
                }
                else if (nav == 2) {
                    // Call Sorting Experiment Function for Linked List with DataSet 1
                    waitToReturn();
                }
                return;
            case 3:
                if (nav == 1) {
                    // Call Sorting Experiment Function for Array with DataSet 1
                    waitToReturn();
                }
                else if (nav == 2) {
                    // Call Sorting Experiment Function for Linked List with DataSet 1
					waitToReturn();
                }
                return;
            default:
                cout << "Invalid choice. Please select a valid option from the menu.\n";
                return;
            }
        }



    }
}


void SearchingMenu(bool display) {
    int nav;
    while (true) {
        //Select Array/Linked List for Searching Experiment
		printSubtitle("Searching Experiment");
		int container = selectDataContainer();
        if (container == 0) {
            cout << "Exiting the program. Goodbye!\n";
            return;
        }
        //Select Data Set for Searching Experiment
        int dataSet = selectDataSet();
        if (dataSet == 0) {
            cout << "Exiting the program. Goodbye!\n";
            return;
        }
        int sorted = selectSorted();
        bool sort;
        if (sorted == 1) sort = false;
        else sort = true;
        SearchingCriteriaMenu(container, dataSet, display, sort);
        waitToReturn();
        return;
    }
}

void ResultMenu() {
    int nav;
    while (true) {
		printSubtitle("Experiment Results");
        cout << "Please select the results you want to compare:\n"
            << "1. Sorting Results\n"
            << "2. Searching Results\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        getInput(nav);
        switch (nav) {
        case 1:
			SortingMenu(false);
            waitToReturn();
            break;
        case 2:
            //Ignores Input, imporantce on display or not (int, int, false, bool)
			SearchingCriteriaMenu(1, 1, false, false);
            waitToReturn();
            break;
        case 0:
            cout << "Returning to previous page.\n";
            return;
        default:
            cout << "Invalid choice. Please select a valid option from the menu.\n";
        }
    }
}


//==================================================================
//==================================================================
//Main Menu
void MainMenu() {
    int nav;
    while (true) {
        printTitle("Main Menu");
        cout << "Welcome to the Program!\n"
            << "Please select an option from the menu below:\n"
            << "1. Age Group Comparison\n"
            << "2. Carbon Emission Analysis\n"
            << "3. Sorting Experiment\n"
            << "4. Searching Experiment\n"
            << "5. Experiment Results\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        getInput(nav);

        switch (nav) {
        case 1:
			//printResidentArray(arr1);
            analyzeAllAgeGroups(arr1.arr, arr1.size, "City A - Metropolitan");
            analyzeAllAgeGroups(arr2.arr, arr2.size, "City B - Suburban");
            analyzeAllAgeGroups(arr3.arr, arr3.size, "City C - Rural");
            
            cout << setfill('=') << setw(60) << "=" << "\n";
            waitToReturn();
            break;
        case 2:
            EmissionMenu();
            break;
        case 3:
            SortingMenu(true);
            break;
        case 4:
            SearchingMenu(true);
            break;
        case 5:
            ResultMenu();
            break;
        case 0:
            cout << setfill('=') << setw(60) << "=" << "\n"
                << "Exiting the program. Goodbye!\n";
            return;
            break;
        default:
            cout << "Invalid choice. Please select a valid option from the menu.\n\n";
        }
    }
}