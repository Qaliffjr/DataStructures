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

void analyzeEmissionByDataset(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);
void analyzeEmissionByMode(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);
void analyzeEmissionByAgeGroup(const ResidentLinkedList& list1, const ResidentLinkedList& list2, const ResidentLinkedList& list3);


// Linked List Functions:
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

void printResidentLinkedList(const ResidentLinkedList& list);


#endif