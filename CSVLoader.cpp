#include "CSVLoader.hpp"
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


void loadCSV(const string& filename, RecordArray& arr, RecordLinkedList& list) {

	//Open the file
    ifstream file(filename);
    string line;

	//Error handling for file opening
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    //Skip header line to not be stored as a record
    getline(file, line);

	//Read each line of the CSV and parse it into a Record struct then store it in both the array and linked list
    while (getline(file, line)) {

		//Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
		string temp;                //Temporary variable for parsing numeric values as strings before converting them

        Record record;

        //ResidentID
        getline(ss, record.ID, ',');

        //Age
        getline(ss, temp, ',');
        record.Age = stoi(temp);

        //Mode of Transport
        getline(ss, record.modeOfTransport, ',');

        //Daily Distance
        getline(ss, temp, ',');
        record.dailyDistance = stoi(temp);

        //Carbon Emission Factor
        getline(ss, temp, ',');
        record.carbonEmission = stof(temp);

        //Monthly Frequency
        getline(ss, temp, ',');
        record.monthlyFrequency = stoi(temp);


		//Insert the record into both the array and linked list
        if (arr.size < arr.capacity) {
            arr.arr[arr.size++] = record;
        }

        // =========================
        // 2. INSERT INTO LINKED LIST
        // =========================
        Node* newNode = new Node{ record, nullptr };

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