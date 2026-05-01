#pragma once //use pragma to ensure that the file is only included once
#include "Resident.hpp"

struct ResidentArray {
    Resident* data;
    int size;
    int capacity;
};

void initArray(ResidentArray& arr); //setting new empty array
void freeArray(ResidentArray& arr); //freeing the array
bool reserveArray(ResidentArray& arr, int newCapacity); //reserving more space for the array
bool pushBack(ResidentArray& arr, const Resident& item); //adding a new resident to the array
ResidentArray copyArray(const ResidentArray& source); //copying the arrzzay