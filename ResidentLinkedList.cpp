#include "ResidentLinkedList.hpp"
#include "tableDisplay.hpp"
#include <chrono>
#include <iostream>

//======================================= Utility Logic ========================================
//Quickly Inserts found Data in the end of a LinkedList
void insertBack(ResidentLinkedList& list, const Resident& data) {

    Node* newNode = new Node{ data, nullptr };

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    }
    else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

void printResidentLinkedList(const ResidentLinkedList& list) {
    Node* current = list.head;
    int index = 0;
    while (current != nullptr) {
        const Resident& r = current->data;
        std::cout << std::left
            << std::setw(4) << index++ << "  "
            << std::setw(8) << r.ID
            << std::setw(6) << r.Age
            << std::setw(16) << r.modeOfTransport
            << std::setw(14) << std::fixed << std::setprecision(1) << r.dailyDistance
            << std::setw(20) << std::fixed << std::setprecision(2) << r.monthlyCarbonEmission
            << "\n";
        current = current->next;
    }
}
//===================================== Carbon Emission Analysis Logic ========================================
//Carbon Emission Analysis for a LinkedList
void analyzeEmissionByDataset(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3) {

    //Start Timer
    auto programStart = std::chrono::high_resolution_clock::now();
    //Prepare Table
    const int COLS = 2;

    std::string headers[COLS] = {
        "Dataset (City)",
        "Total Emission",
    };

    int widths[COLS] = {
    50,  // Dataset
    30,  // Total Emission
    };
    std::string rows[5][10];
    int rowCount = 3;
    rows[0][0] = "City A - Metropolitan";
    rows[1][0] = "City B - Suburban";
    rows[2][0] = "City C - Rural";


	//Calculate Total Emission for each dataset
    //List 1
    int tmp = 0;
    Node* current = list1.head;

    while (current != nullptr) {
        tmp += current->data.monthlyCarbonEmission;
        current = current->next;
    }
	rows[0][1] = std::to_string(tmp) + " kg CO2";

    //List 2
    tmp = 0;
    current = list2.head;

    while (current != nullptr) {
        tmp += current->data.monthlyCarbonEmission;
        current = current->next;
    }
    rows[1][1] = std::to_string(tmp) + " kg CO2";

    //List 3
    tmp = 0;
    current = list3.head;

    while (current != nullptr) {
        tmp += current->data.monthlyCarbonEmission;
        current = current->next;
    }
    rows[2][1] = std::to_string(tmp) + " kg CO2";

	printTable(headers, COLS, rows, rowCount, widths);
    auto programEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = programEnd - programStart;

    //Display Process Time
    std::cout << "[Process time: " << std::fixed << std::setprecision(4) << elapsed.count() << " ms]\n";
}

void analyzeEmissionByMode(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3) {
    //Start Timer
    auto programStart = std::chrono::high_resolution_clock::now();

	//Prepare Table
    const int COLS = 6;

    std::string headers[COLS] = {
        "Mode of Transport",
        "Total Residents",
        "City A - Metropolitan",
        "City B - Suburban",
        "City C - Rural",
        "Total Emission",
    };

    int widths[COLS] = {
    20,  // Mode of Transport
    20,  // Total Residents
    30,  // City A - Metropolitan
    30,  // City B - Suburban
    30,  // City C - Rural
    30,  // Total Emission
    };
    std::string rows[6][10];
    int rowCount = 6;
    rows[0][0] = "Bicycle";
    rows[1][0] = "Bus";
    rows[2][0] = "Car";
    rows[3][0] = "Carpool";
    rows[4][0] = "School Bus";
    rows[5][0] = "Walking";

    int bicycleA = 0, busA = 0, carA = 0, carpoolA = 0, schoolBusA = 0, walkingA = 0;
    int bicycleB = 0, busB = 0, carB = 0, carpoolB = 0, schoolBusB = 0, walkingB = 0;
    int bicycleC = 0, busC = 0, carC = 0, carpoolC = 0, schoolBusC = 0, walkingC = 0;
	int bicycleCount = 0, busCount = 0, carCount = 0, carpoolCount = 0, schoolBusCount = 0, walkingCount = 0;

	//Calculate Emission for each mode of transport in each dataset
    //List 1
    Node* current = list1.head;
    while (current != nullptr) {
        if (current->data.modeOfTransport == "Bicycle") {
            bicycleA += current->data.monthlyCarbonEmission;
            bicycleCount++;
		}
        else if (current->data.modeOfTransport == "Bus") {
            busA += current->data.monthlyCarbonEmission;
            busCount++;
        }
        else if (current->data.modeOfTransport == "Car") {
            carA += current->data.monthlyCarbonEmission;
            carCount++;
        }
        else if (current->data.modeOfTransport == "Carpool") {
            carpoolA += current->data.monthlyCarbonEmission;
            carpoolCount++;
        }
        else if (current->data.modeOfTransport == "School Bus") {
            schoolBusA += current->data.monthlyCarbonEmission;
            schoolBusCount++;
        }
        else if (current->data.modeOfTransport == "Walking") walkingA += current->data.monthlyCarbonEmission;
        current = current->next;
    }

    //List 2
    current = list2.head;
    while (current != nullptr) {
        if (current->data.modeOfTransport == "Bicycle") {
            bicycleB += current->data.monthlyCarbonEmission;
            bicycleCount++;
        }
        else if (current->data.modeOfTransport == "Bus") {
            busB += current->data.monthlyCarbonEmission;
            busCount++;
        }
        else if (current->data.modeOfTransport == "Car") {
            carB += current->data.monthlyCarbonEmission;
            carCount++;
        }
        else if (current->data.modeOfTransport == "Carpool") {
            carpoolB += current->data.monthlyCarbonEmission;
            carpoolCount++;
        }
        else if (current->data.modeOfTransport == "School Bus") {
            schoolBusB += current->data.monthlyCarbonEmission;
            schoolBusCount++;
        }
        else if (current->data.modeOfTransport == "Walking") {
            walkingB += current->data.monthlyCarbonEmission;
            walkingCount++;
        }
        current = current->next;
    }

    //List 3
    current = list3.head;
    while (current != nullptr) {
        if (current->data.modeOfTransport == "Bicycle") {
            bicycleC += current->data.monthlyCarbonEmission;
            bicycleCount++;
        }
        else if (current->data.modeOfTransport == "Bus") {
            busC += current->data.monthlyCarbonEmission;
            busCount++;
        }
        else if (current->data.modeOfTransport == "Car") {
            carC += current->data.monthlyCarbonEmission;
            carCount++;
        }
        else if (current->data.modeOfTransport == "Carpool") {
            carpoolC += current->data.monthlyCarbonEmission;
            carpoolCount++;
        }
        else if (current->data.modeOfTransport == "School Bus") {
            schoolBusC += current->data.monthlyCarbonEmission;
            schoolBusCount++;
        }
        else if (current->data.modeOfTransport == "Walking") {
            walkingC += current->data.monthlyCarbonEmission;
            walkingCount++;
        }
        current = current->next;
    }
    //Insert Data to Rows
	rows[0][1] = std::to_string(bicycleCount) + " Residents";
    rows[0][2] = std::to_string(bicycleA) + " kg CO2";
    rows[0][3] = std::to_string(bicycleB) + " kg CO2";
    rows[0][4] = std::to_string(bicycleC) + " kg CO2";
    rows[0][5] = std::to_string(bicycleA + bicycleB + bicycleC) + " kg CO2";

    rows[1][1] = std::to_string(busCount) + " Residents";
    rows[1][2] = std::to_string(busA) + " kg CO2";
    rows[1][3] = std::to_string(busB) + " kg CO2";
    rows[1][4] = std::to_string(busC) + " kg CO2";
    rows[1][5] = std::to_string(busA + busB + busC) + " kg CO2";    
   
	rows[2][1] = std::to_string(carCount) + " Residents";
    rows[2][2] = std::to_string(carA) + " kg CO2";
    rows[2][3] = std::to_string(carB) + " kg CO2";
    rows[2][4] = std::to_string(carC) + " kg CO2";
    rows[2][5] = std::to_string(carA + carB + carC) + " kg CO2";

    rows[3][1] = std::to_string(carpoolCount) + " Residents";
    rows[3][2] = std::to_string(carpoolA) + " kg CO2";
    rows[3][3] = std::to_string(carpoolB) + " kg CO2";
    rows[3][4] = std::to_string(carpoolC) + " kg CO2";
    rows[3][5] = std::to_string(carpoolA + carpoolB + carpoolC) + " kg CO2";

    rows[4][1] = std::to_string(schoolBusCount) + " Residents";
    rows[4][2] = std::to_string(schoolBusA) + " kg CO2";
    rows[4][3] = std::to_string(schoolBusB) + " kg CO2";
    rows[4][4] = std::to_string(schoolBusC) + " kg CO2";
    rows[4][5] = std::to_string(schoolBusA + schoolBusB + schoolBusC) + " kg CO2";

    rows[5][1] = std::to_string(walkingCount) + " Residents";
    rows[5][2] = std::to_string(walkingA) + " kg CO2";
    rows[5][3] = std::to_string(walkingB) + " kg CO2";
    rows[5][4] = std::to_string(walkingC) + " kg CO2";
    rows[5][5] = std::to_string(walkingA + walkingB + walkingC) + " kg CO2";

    //Display Table
	printTable(headers, COLS, rows, rowCount, widths);
    auto programEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = programEnd - programStart;

    //Display Process Time
    std::cout << "[Process time: " << std::fixed << std::setprecision(4) << elapsed.count() << " ms]\n";

}

void analyzeEmissionByAgeGroup(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3) {
	//Start Timer
    auto programStart = std::chrono::high_resolution_clock::now();

	//Prepare Table
    const int COLS = 5;

    std::string headers[COLS] = {
        "Age Group",
        "City A",
		"City B",
        "City C",
		"Total Emission",
    };

    int widths[COLS] = {
    50,  // Age Group
    20,  // City A
    20,  // City B
    20,  // City C
    20,  // Total Emission
    };
    std::string rows[5][10];
    int rowCount = 5;
    rows[0][0] = "Children & Teenagers (6-17)";
    rows[1][0] = "University Students & Young Adults (18-25)";
    rows[2][0] = "Working Adults (Early Career) (26 - 45)";
    rows[3][0] = "Working Adults (Late Career) (46 - 60)";
    rows[4][0] = "Senior Citizens / Retirees (61-100)";


	Node* current = list1.head;
    double ageGroupA[5] = { 0 };
    double ageGroupB[5] = { 0 };
    double ageGroupC[5] = { 0 };
    while (current != nullptr) {
        int age = current->data.Age;
        double emission = current->data.monthlyCarbonEmission;
        if (age >= 6 && age <= 17) {
            ageGroupA[0] += emission;
        }
        else if (age >= 18 && age <= 25) {
            ageGroupA[1] += emission;
        }
        else if (age >= 26 && age <= 45) {
            ageGroupA[2] += emission;
        }
        else if (age >= 46 && age <= 60) {
            ageGroupA[3] += emission;
        }
        else if (age >= 61 && age <= 100) {
            ageGroupA[4] += emission;
        }
        current = current->next;
	}

	current = list2.head;
    while (current != nullptr) {
        int age = current->data.Age;
        double emission = current->data.monthlyCarbonEmission;
        if (age >= 6 && age <= 17) {
            ageGroupB[0] += emission;
        }
        else if (age >= 18 && age <= 25) {
            ageGroupB[1] += emission;
        }
        else if (age >= 26 && age <= 45) {
            ageGroupB[2] += emission;
        }
        else if (age >= 46 && age <= 60) {
            ageGroupB[3] += emission;
        }
        else if (age >= 61 && age <= 100) {
            ageGroupB[4] += emission;
        }
        current = current->next;
	}

	current = list3.head;
    while (current != nullptr) {
        int age = current->data.Age;
        double emission = current->data.monthlyCarbonEmission;
        if (age >= 6 && age <= 17) {
            ageGroupC[0] += emission;
        }
        else if (age >= 18 && age <= 25) {
            ageGroupC[1] += emission;
        }
        else if (age >= 26 && age <= 45) {
            ageGroupC[2] += emission;
        }
        else if (age >= 46 && age <= 60) {
            ageGroupC[3] += emission;
        }
        else if (age >= 61 && age <= 100) {
            ageGroupC[4] += emission;
        }
        current = current->next;
    }

    //Insert Rows
    for (int i = 0; i < 5; i++) {
        rows[i][1] = std::to_string(ageGroupA[i]) + " kg CO2";
        rows[i][2] = std::to_string(ageGroupB[i]) + " kg CO2";
        rows[i][3] = std::to_string(ageGroupC[i]) + " kg CO2";
        rows[i][4] = std::to_string(ageGroupA[i] + ageGroupB[i] + ageGroupC[i]) + " kg CO2";
	}
    //Display Table
	printTable(headers, COLS, rows, rowCount, widths);
    auto programEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = programEnd - programStart;

	//Display Process Time
    std::cout << "[Process time: " << std::fixed << std::setprecision(4) << elapsed.count() << " ms]\n";

}



//======================================= Searching Logics ===================================
//====================== Unsorted Linked List ==========================
//Age Group Searching
ResidentLinkedList linearSearchListByAge(const ResidentLinkedList& list, int minAge, int maxAge) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        int age = current->data.Age;

        if (age >= minAge && age <= maxAge) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}


//Mode of Transport Searching
ResidentLinkedList linearSearchListByTransport(const ResidentLinkedList& list, const std::string& modeOfTransport) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        if (current->data.modeOfTransport == modeOfTransport) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}


//Daily Distance Threshold Searching
ResidentLinkedList linearSearchListByDailyDistance(const ResidentLinkedList& list, double minDistance, double maxDistance) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        int dist = current->data.dailyDistance;

        if (dist >= minDistance && dist <= maxDistance) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}


ResidentLinkedList linearSearchListByEmission(const ResidentLinkedList& list, double threshold) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        double emission = current->data.monthlyCarbonEmission;
        if (emission > threshold) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}



