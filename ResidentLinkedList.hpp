#ifndef RESIDENT_LINKED_LIST_HPP
#define RESIDENT_LINKED_LIST_HPP


#pragma once
#include <string>
#include "Resident.hpp"

struct Node {
    Resident data;
    Node* next;
};

struct ResidentLinkedList {
    Node* head;
    Node* tail;
};

void insertBack(ResidentLinkedList& list, const Resident& data);

//Analyze Emission Functions:
void analyzeEmissionByDataset(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);
void analyzeEmissionByMode(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);
void analyzeEmissionByAgeGroup(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);


// Search Linked List Functions:
// Unsorted
ResidentLinkedList linearSearchListByAge(
    const ResidentLinkedList& list,
    int minAge,
    int maxAge
);

ResidentLinkedList linearSearchListByTransport(
    const ResidentLinkedList& list,
    const std::string& modeOfTransport
);

ResidentLinkedList linearSearchListByDailyDistance(
    const ResidentLinkedList& list, 
    double minDistance, 
    double maxDistance);

ResidentLinkedList linearSearchListByEmission(
    const ResidentLinkedList& list,
    double threshold
);

//Sorted
Node* findStartNode(Node* head, double minValue, int sortBy);
ResidentLinkedList searchListByAge(Node* head, int minAge, int maxAge);
ResidentLinkedList searchListByDistance(Node* head, int minDist, int maxDist);
ResidentLinkedList searchListByTransport(Node* head, const std::string& mode);
ResidentLinkedList searchListByEmission(Node* head, double threshold);
void runSearch(Node* head);


//Others
void printResidentLinkedList(const ResidentLinkedList& list);

//Sorting
void sortList(Node*& head, int sortBy);
void sortedInsert(Node*& sortedHead, Node* newNode, int sortBy);
bool isSmaller(Node* a, Node* b, int sortBy);


#endif