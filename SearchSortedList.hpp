#pragma once
#include "recordLinkedList.hpp"
#include <string>
using namespace std;

Node* findStartNode(Node* head, double minValue, int sortBy);
void searchByAge(Node* head, int minAge, int maxAge);
void searchByDistance(Node* head, int minDist, int maxDist);
//void searchByTransport(Node* head, const string& mode);
void runSearch(Node* head);