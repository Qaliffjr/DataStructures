#include "ResidentArray.hpp"
#include <new> // for std::nothrow

void initArray(ResidentArray& arr) {
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void freeArray(ResidentArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

bool reserveArray(ResidentArray& arr, int newCapacity) {
    if (newCapacity <= arr.capacity) return true;

    Resident* newData = new (std::nothrow) Resident[newCapacity];
    if (!newData) return false;

    for (int i = 0; i < arr.size; ++i) {
        newData[i] = arr.data[i];
    }

    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
    return true;
}

bool pushBack(ResidentArray& arr, const Resident& item) {
    if (arr.size == arr.capacity) {
        int nextCap = (arr.capacity == 0) ? 8 : arr.capacity * 2;
        if (!reserveArray(arr, nextCap)) return false;
    }

    arr.data[arr.size] = item;
    arr.size++;
    return true;
}

ResidentArray copyArray(const ResidentArray& source) {
    ResidentArray copy;
    initArray(copy);

    if (!reserveArray(copy, source.size)) return copy;

    for (int i = 0; i < source.size; ++i) {
        copy.data[i] = source.data[i];
    }
    copy.size = source.size;
    return copy;
}