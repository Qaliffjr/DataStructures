#include "linearSearch.hpp"

// Doesnt use "using namespace std;" because only needed for string::


//======================================= Extra Logic ========================================
//Quickly Inserts found Data in the end of a LinkedList
void insertBack(ResidentLinkedList& list, const Resident& data) {

    Node* newNode = new Node{ data, nullptr };

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    }
    else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
}


//======================================= Searching Logics ===================================
//========================= Array =============================
//Insert Iean's Code



//====================== Linked List ==========================
//Age Group Searching

ResidentLinkedList linearSearchListByAge(const ResidentLinkedList& list, int minAge, int maxAge) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        int age = current->data.Age;

        if (age >= minAge && age <= maxAge) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}


//Mode of Transport Searching
ResidentLinkedList linearSearchListByTransport(const ResidentLinkedList& list, const std::string& modeOfTransport) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        if (current->data.modeOfTransport == modeOfTransport) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}


//Daily Distance Threshold Searching
ResidentLinkedList linearSearchListByDailyDistance(const ResidentLinkedList& list, int minDistance, int maxDistance) {
    ResidentLinkedList result;
    result.head = nullptr;
    result.tail = nullptr;

    Node* current = list.head;

    while (current != nullptr) {
        int dist = current->data.dailyDistance;

        if (dist >= minDistance && dist <= maxDistance) {
            insertBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}