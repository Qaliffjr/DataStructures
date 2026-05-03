#include "LinkedList.hpp"
#include <iostream>
using namespace std;

//compare 2 nodes base on sortBy
bool isSmaller(Node* a, Node* b, int sortBy) {
	if (sortBy == 1) {
		return a->data.Age < b->data.Age;
	}
	else if (sortBy == 2) {
		return a->data.dailyDistance < b->data.dailyDistance;
	}
	else if (sortBy == 3) {
		return a->data.carbonEmission < b->data.carbonEmission;
	}
	//when a bigger than b
	else{
		return false;
	}
}

//
void sortedInsert(Node*& sortedHead, Node* newNode, int sortBy) {
	//when a<b: 
	if (sortedHead == nullptr || isSmaller(newNode, sortedHead, sortBy)) {
		
		newNode->next = sortedHead;
		sortedHead = newNode;
	}
	else {
		//when a>b, search the position
		Node* current = sortedHead;
		
		//find correct position
		while (current->next != nullptr && !isSmaller(newNode, current->next, sortBy)) {
			current = current->next;
		}

		//insert newNode after current
		newNode->next = current->next;
		current->next = newNode;
	}
}

//Check each node one by one
void sortList(Node*& head, int sortBy) {
	
	Node* sortedHead = nullptr;
	Node* current = head;

	//continue until end of the list
	while (current != nullptr) {
		Node* nextNode = current->next;
		sortedInsert(sortedHead, current, sortBy);
		current = nextNode;
	}
	head = sortedHead;
}

//check sorted list
void displayList(Node* head) {
	if (head == nullptr) {
		cout << "empty" << endl;
		return;
	}
	Node* current = head;
	int count = 1;
	while (current != nullptr) {
		cout << "--- Node " << count << " ---" << endl;
		cout << "ID: " << current->data.ID << endl;
		cout << "Age: " << current->data.Age << endl;
		cout << "Mode of Transport: " << current->data.modeOfTransport << endl;
		cout << "Daily Distance: " << current->data.dailyDistance << endl;
		cout << "Carbon Emission: " << current->data.carbonEmission << endl;
		cout << "Monthly Frequency: " << current->data.monthlyFrequency << endl;
		cout << "Monthly Carbon Emission: " << current->data.monthlyCarbonEmission << endl;
		current = current->next;
		count++;
	}
}

