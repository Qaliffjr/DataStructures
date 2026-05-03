#include "menu.hpp"
#include "ResidentArray.hpp"
#include "dataStore.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;


//==================================================================
//==================================================================
//==================================================================
//Helper Functions for Menus
void printTitle(string text, int width = 60) {
    int padding = (width - text.length()) / 2;
    cout << setfill('=') << setw(width) << "=" << "\n"
        << setfill(' ')
        << setw(padding + text.length()) << text << "\n"
        << setfill('=') << setw(width) << "=" << "\n";
}

void printSubtitle(string text, int width = 60) {
    int padding = (width - text.length()) / 2;
    cout << "\n\n"
        << setfill('-') << setw(width) << "-" << "\n"
        << setfill(' ')
        << setw(padding + text.length()) << text << "\n"
        << setfill('-') << setw(width) << "-" << "\n";
}

void displayProcessTime(chrono::duration<double, milli> ms) {
    cout << "\n  [Process time: " << fixed << setprecision(4) << ms.count() << " ms]\n";
}


void waitToReturn() {
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
	cout << "\n\n\n";
}

//Extra Logic for Criterias

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
//Selection Menus

int selectAgeGroup() {
    int group;
    cout << "\nPlease select an age group from the menu below:\n"
        << "1. Children & Teenagers (6-17)"
        << "2. University Students / Young Adults (18-25)"
        << "3. Working Adults - Early Career (26-45)"
        << "4. Working Adults - Late Career (46-60)"
        << "5. Senior Citizens / Retirees (61-100)"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    cin >> group;
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
    cin >> mode;
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
    cin >> mode;
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
    cin >> mode;
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
    cin >> group;
    return group;
}

int selectDataSet() {
    int dataSet;
    cout << "Please select a dataset from the menu below:\n"
        << "1. City A - Metropolitan\n"
        << "2. City B - University Town\n"
        << "3. City C - Suburban/Rural\n"
        << "0. Return\n"
        << setfill('-') << setw(60) << "-" << "\n"
        << "Enter your choice: ";
    cin >> dataSet;
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
    cin >> container;
    return container;
}


//==================================================================
//==================================================================
//==================================================================
//Level 2 Menus

void SearchingCriteriaMenu(int container, int dataSet, bool showResult) {
	//Also Remember to Display Selected Criteria on the Result Page 
    int nav;
    cout << "Please select a searching criteria from the menu below:\n"
        << "1. Search by Age Group\n"
        << "2. Search by Mode of Transport\n"
        << "3. Search by Daily Distance Traveled\n"
        << "0. Exit\n" 
        << setfill('-') << setw(60) << "-" << "\n"
		<< "Enter your choice: ";
    cin >> nav;
	if (nav == 0) {
        cout << "Returning to previous page.\n";
        return;
    }

    int aGroup, mode, dGroup, min, max;
    switch (nav) {
    case 1:
        aGroup = selectAgeGroup();
        if (aGroup == 0) {
            cout << "Returning to previous page.\n";
            return;
        }
        else {
            // Call Searching Function based on container and dataSet for Age Group Criteria
            // searchResult result = searchByAgeGroup(container, dataSet, minAge, maxAge);
            // Display Results
            // Display TIme & Memory Used
        }
        break;
    case 2:
        if (dataSet == 1) {
            mode = selectTransportMode1();
            if (mode == 0) {
                cout << "Returning to previous page.\n";
                return;
            }
            else {
                // Call Searching Function based on container and dataSet for Mode of Transport Criteria
                // Display Results
                // Display TIme & Memory Used
            }
        }
        else if (dataSet == 2) {
            mode = selectTransportMode2();
            if (mode == 0) {
                cout << "Returning to previous page.\n";
                return;
            }
            else {
                // Call Searching Function based on container and dataSet for Mode of Transport Criteria
                // Display Results
                // Display TIme & Memory Used
            }
		}
        else {
            mode = selectTransportMode3();
            if (mode == 0) {
                cout << "Returning to previous page.\n";
                return;
            }
            else {
                // Call Searching Function based on container and dataSet for Mode of Transport Criteria
                // Display Results
                // Display TIme & Memory Used
			}
        }
        break;
    case 3:
        dGroup = selectDailyDistanceGroup();
        if (dGroup == 0) {
            cout << "Returning to previous page.\n";
            return;
        }
        else {
            min = getMinDistance(dGroup);
            max = getMaxDistance(dGroup);
            // Call Searching Function based on container and dataSet for Daily Distance Traveled Criteria
            // Display Results
            // Display TIme & Memory Used
        }
		break;
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
            << "1. Compare Carbon Emissions by Age Group\n"
            << "2. Compare Carbon Emissions by Mode of Transport\n"
            << "3. Compare Carbon Emissions by Daily Distance Traveled\n"
            << "0. Exit\n"
            << setfill('=') << setw(60) << "=" << "\n"
            << "Enter your choice: ";
        cin >> nav;
        switch (nav) {
        case 1:
            // Call Function to Compare Carbon Emissions by Age Group & Display Results
            waitToReturn();
            return;
        case 2:
            // Call Function to Compare Carbon Emissions by Mode of Transport & Display Results
            waitToReturn();
            return;
        case 3:
            // Call Function to Compare Carbon Emissions by Daily Distance Traveled & Display Results
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
        cin >> nav;

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
        else {
            SearchingCriteriaMenu(container, dataSet, display);
			waitToReturn();
            return;
        }
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
        cin >> nav;
        switch (nav) {
        case 1:
			SortingMenu(false);
            break;
        case 2:
			SearchingMenu(false);
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
        cin >> nav;

        switch (nav) {
        case 1:
            analyzeAllAgeGroups(arr1.arr, arr1.size, "City A - Metropolitan");
            
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