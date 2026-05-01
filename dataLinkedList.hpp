#pragma once
#include <string>

struct Node {
	std::string ID;
	int Age;
	std::string modeOfTransport;
	int dailyDistance;
	float carbonEmission;
	int monthlyFrequency;

	Node* next;
};
