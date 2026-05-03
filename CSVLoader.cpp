#include "CSVLoader.hpp"
#include "Resident.hpp"
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;


int countLines(const string& filename) {
    ifstream file(filename);
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }

    return count;
}


void loadCSV(const string& filename, ResidentArray& arr, ResidentLinkedList& list) {

    //Open the file
    ifstream file(filename);
    string line;

    //Error handling for file opening
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    //Skip header line to not be stored as a Resident
    getline(file, line);

    //Read each line of the CSV and parse it into a Resident struct then store it in both the array and linked list
    while (getline(file, line)) {

        //Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;                //Temporary variable for parsing numeric values as strings before converting them

        Resident Resident;

        //ResidentID
        getline(ss, Resident.ID, ',');

        //Age
        getline(ss, temp, ',');
        Resident.Age = stoi(temp);

        //Mode of Transport
        getline(ss, Resident.modeOfTransport, ',');

        //Daily Distance
        getline(ss, temp, ',');
        Resident.dailyDistance = stod(temp); //change from stoi to stod

        //Carbon Emission Factor
        getline(ss, temp, ',');
        Resident.carbonEmissionFactor = stod(temp);

        //Monthly Frequency
        getline(ss, temp, ',');
        Resident.averageDayPerMonth = stoi(temp);
        //Monthly Carbon Emission
        Resident.monthlyCarbonEmission = Resident.dailyDistance * Resident.carbonEmissionFactor * Resident.averageDayPerMonth;


        //=====================================================
        //Insert the Resident into both the array and linked list
        //1. Array
        if (arr.size < arr.capacity) {
            arr.arr[arr.size++] = Resident;
        }

        //2. Linked List
        Node* newNode = new Node{ Resident, nullptr };

        if (list.head == nullptr) {
            list.head = list.tail = newNode;
        }
        else {
            list.tail->next = newNode;
            list.tail = newNode;
        }
    }

    file.close();
}
