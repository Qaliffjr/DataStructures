#include "DataStore.hpp"


//Initializing the array & linked list variables that will be used across the main program
// Arrays
ResidentArray arr1;
ResidentArray arr2;
ResidentArray arr3;
ResidentArray arrCombined;

// Linked Lists
ResidentLinkedList list1;
ResidentLinkedList list2;
ResidentLinkedList list3;
ResidentLinkedList listCombined;


//==================
//Combine Array
ResidentArray combineArrays(
    const ResidentArray& a,
    const ResidentArray& b,
    const ResidentArray& c
) {
    ResidentArray combined;
    combined.size = a.size + b.size + c.size;
    combined.capacity = combined.size;
    combined.arr = new Resident[combined.capacity];

    int index = 0;

    for (int i = 0; i < a.size; ++i) {
        combined.arr[index++] = a.arr[i];
    }

    for (int i = 0; i < b.size; ++i) {
        combined.arr[index++] = b.arr[i];
    }

    for (int i = 0; i < c.size; ++i) {
        combined.arr[index++] = c.arr[i];
    }

    return combined;
}


//==================
//Combine LinkedList
void insertNode(ResidentLinkedList& list, const Resident& r) {
    Node* newNode = new Node{ r, nullptr };

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    }
    else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

ResidentLinkedList combineLists(
    const ResidentLinkedList& a,
    const ResidentLinkedList& b,
    const ResidentLinkedList& c
) {
    ResidentLinkedList result;
    result.head = result.tail = nullptr;

    Node* curr;

    curr = a.head;
    while (curr) {
        insertNode(result, curr->data);
        curr = curr->next;
    }

    curr = b.head;
    while (curr) {
        insertNode(result, curr->data);
        curr = curr->next;
    }

    curr = c.head;
    while (curr) {
        insertNode(result, curr->data);
        curr = curr->next;
    }

    return result;
}