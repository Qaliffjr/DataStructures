#ifndef LOADDATA_HPP
#define LOADDATA_HPP

#include <string>
#include <sstream>

using namespace std;

struct Node {
	std::string ID;
	int Age;
	std::string modeOfTransport;
	int dailyDistance;
	float carbonEmission;
	int monthlyFrequency;
	Node* next;
};

extern Node* head;

void loadData(const string& fileName, Node*& head);
#endif
