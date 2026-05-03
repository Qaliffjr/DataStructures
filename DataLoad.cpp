#include "loadData.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void loadData(const string& fileName, Node*& head) {

	//load selected file and upload data to linked list.
	//Open file
	ifstream file(fileName);

	if (!file.is_open()) {
		cout << "Cannot open file: " << fileName << endl;
		return;
	}

	//Read file line by line and insert into linked list.
	string line;

	// Skip header line
	getline(file, line); 

	// Read each line of the file and create a new node
	while (getline(file, line)) {
		
		stringstream ss(line);
		string temp;

		Node* newNode = new Node();

		getline(ss, newNode->ID, ',');
		
		getline(ss, temp, ',');
		newNode->Age = stoi(temp);

		getline(ss, newNode->modeOfTransport, ',');

		getline(ss, temp, ',');
		newNode->dailyDistance = stoi(temp);

		getline(ss, temp, ',');
		newNode->carbonEmission = stof(temp);

		getline(ss, temp, ',');
		newNode->monthlyFrequency = stoi(temp);
		
		newNode->next = nullptr;

		//Pointer
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node* current = head;

			while (current->next != nullptr) {
				current = current->next;
			}

			current->next = newNode;
		}
	}

}

