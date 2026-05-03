#include "ResidentArrayUtils.hpp"
#include "CSVLoader.hpp"

#include <iostream>

void initResidentArray(ResidentArray& arr, int capacity) {
    arr.size = 0;
    arr.capacity = capacity;
    arr.arr = new Resident[capacity];
}

void freeResidentArray(ResidentArray& arr) {
    delete[] arr.arr;
    arr.arr = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

ResidentArray copyResidentArray(const ResidentArray& source) {
    ResidentArray copy;
    copy.size = source.size;
    copy.capacity = source.size;
    copy.arr = new Resident[copy.capacity];

    for (int i = 0; i < source.size; ++i) {
        copy.arr[i] = source.arr[i];
    }

    return copy;
}

void initResidentLinkedList(ResidentLinkedList& list) {
    list.head = nullptr;
    list.tail = nullptr;
}

void freeResidentLinkedList(ResidentLinkedList& list) {
    Node* current = list.head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    list.head = nullptr;
    list.tail = nullptr;
}

bool loadDataset(
    const std::string& filename,
    ResidentArray& arr,
    ResidentLinkedList& list
) {
    int lineCount = countLines(filename);

    if (lineCount <= 1) {
        std::cout << "Cannot load dataset or dataset is empty: " << filename << "\n";
        return false;
    }

    initResidentArray(arr, lineCount - 1);
    initResidentLinkedList(list);

    loadCSV(filename, arr, list);

    if (arr.size == 0) {
        std::cout << "No residents loaded from: " << filename << "\n";
        freeResidentArray(arr);
        freeResidentLinkedList(list);
        return false;
    }

    return true;
}