#ifndef DATASTORE_HPP
#define DATASTORE_HPP

#include "ResidentArray.hpp"
#include "ResidentLinkedList.hpp"

// Arrays
extern ResidentArray arr1;
extern ResidentArray arr2;
extern ResidentArray arr3;
extern ResidentArray arrCombined;

// Linked Lists
extern ResidentLinkedList list1;
extern ResidentLinkedList list2;
extern ResidentLinkedList list3;
extern ResidentLinkedList listCombined;


ResidentArray combineArrays(
    const ResidentArray& a,
    const ResidentArray& b,
    const ResidentArray& c
);

void insertNode(ResidentLinkedList& list, const Resident& r);

ResidentLinkedList combineLists(
    const ResidentLinkedList& a,
    const ResidentLinkedList& b,
    const ResidentLinkedList& c
);

#endif