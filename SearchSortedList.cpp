#include "SearchSortedList.hpp"

#include "ResidentLinkedList.hpp"
#include "ResidentArrayUtils.hpp"

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
        return a->data.monthlyCarbonEmission < b->data.monthlyCarbonEmission;
    }
    else if (sortBy == 4) {
        return a->data.modeOfTransport < b->data.modeOfTransport;
    }
    //when a bigger than b
    else {
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


//find start node
Node* findStartNode(Node* head, double minValue, int sortBy) {
    int length = 0;
    Node* current = head;

    while (current != nullptr) {
        length++;
        current = current->next;
    }

    int left = 0;
    int right = length - 1;
    Node* result = nullptr;

    while (left <= right) {
        //mid index
        int mid = (left + right) / 2;
        //start - mid
        Node* midNode = head;
        for (int i = 0; i < mid; i++) {
            midNode = midNode->next;
        }
        // sortBy what?
        double midValue;
        if (sortBy == 1)      midValue = midNode->data.Age;
        else if (sortBy == 2) midValue = midNode->data.dailyDistance;
        else if (sortBy == 3) midValue = midNode->data.monthlyCarbonEmission;

        //right
        if (midValue >= minValue) {
            result = midNode;
            right = mid - 1;
        }
        //left
        else {
            left = mid + 1;
        }
    }
    return result;
}


// ============================================================
// Search by Age Group
// ============================================================
//6-17, 18-25, 26-45, 46-60, 61-100

ResidentLinkedList searchListByAge(Node* head, int minAge, int maxAge) {

    ResidentLinkedList result;
    initResidentLinkedList(result);

    //Binary Implementation
    Node* startNode = findStartNode(head, minAge, 1);

    if (startNode == nullptr) {
        return result;
    }

    Node* current = startNode;

    while (current != nullptr && current->data.Age <= maxAge) {

        insertBack(result, current->data);

        current = current->next;
    }

    return result;
}


// ============================================================
//  Search by Distance
// ============================================================
//< 5 KM,6 - 15 KM,> 15 KM
ResidentLinkedList searchListByDistance(Node* head, int minDist, int maxDist) {

    ResidentLinkedList result;
    initResidentLinkedList(result);

    //Binary Implementation
    Node* startNode = findStartNode(head, minDist, 2);

    if (startNode == nullptr) {
        return result;
    }

    Node* current = startNode;

    while (current != nullptr && current->data.dailyDistance <= maxDist) {

        insertBack(result, current->data);

        current = current->next;
    }

    return result;
}

// ============================================================
// Search by Transport Mode
// ============================================================
//bicycle, bus, car, carpool, school bus, walking
ResidentLinkedList searchListByTransport(Node* head, const string& mode) {

    ResidentLinkedList result;
    initResidentLinkedList(result);

    sortList(head, 4);

    Node* current = head;

    while (current != nullptr) {

        if (current->data.modeOfTransport == mode) {
            insertBack(result, current->data);
        }

        current = current->next;
    }

    return result;
}


// ============================================================
// Search by Monthly Emission
// ============================================================
ResidentLinkedList searchListByEmission(Node* head, double threshold) {
    ResidentLinkedList result;
    initResidentLinkedList(result);

    sortList(head, 3);
    //Binary Implementation
    Node* startNode = findStartNode(head, threshold, 3);

    if (startNode == nullptr) {
        return result;
    }

    Node* current = startNode;

    while (current != nullptr && current->data.monthlyCarbonEmission >= threshold) {

        insertBack(result, current->data);

        current = current->next;
    }

    return result;
}
