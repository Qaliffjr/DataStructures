#ifndef RESIDENT_ARRAY_UTILS_HPP
#define RESIDENT_ARRAY_UTILS_HPP

#include <string>
#include "residentArray.hpp"
#include "residentLinkedList.hpp"

void initResidentArray(ResidentArray& arr, int capacity);
void freeResidentArray(ResidentArray& arr);
ResidentArray copyResidentArray(const ResidentArray& source);

void initResidentLinkedList(ResidentLinkedList& list);
void freeResidentLinkedList(ResidentLinkedList& list);

bool loadDataset(
    const std::string& filename,
    ResidentArray& arr,
    ResidentLinkedList& list
);



#endif