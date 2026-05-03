#include "RecordArrayUtils.hpp"
#include "CSVLoader.hpp"

#include <iostream>

void initRecordArray(RecordArray& arr, int capacity) {
    arr.size = 0;
    arr.capacity = capacity;
    arr.arr = new Record[capacity];
}

void freeRecordArray(RecordArray& arr) {
    delete[] arr.arr;
    arr.arr = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

RecordArray copyRecordArray(const RecordArray& source) {
    RecordArray copy;
    copy.size = source.size;
    copy.capacity = source.size;
    copy.arr = new Record[copy.capacity];

    for (int i = 0; i < source.size; ++i) {
        copy.arr[i] = source.arr[i];
    }

    return copy;
}

void initRecordLinkedList(RecordLinkedList& list) {
    list.head = nullptr;
    list.tail = nullptr;
}

void freeRecordLinkedList(RecordLinkedList& list) {
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
    RecordArray& arr,
    RecordLinkedList& list
) {
    int lineCount = countLines(filename);

    if (lineCount <= 1) {
        std::cout << "Cannot load dataset or dataset is empty: " << filename << "\n";
        return false;
    }

    initRecordArray(arr, lineCount - 1);
    initRecordLinkedList(list);

    loadCSV(filename, arr, list);

    if (arr.size == 0) {
        std::cout << "No records loaded from: " << filename << "\n";
        freeRecordArray(arr);
        freeRecordLinkedList(list);
        return false;
    }

    return true;
}

RecordArray combineArrays(
    const RecordArray& a,
    const RecordArray& b,
    const RecordArray& c
) {
    RecordArray combined;
    combined.size = a.size + b.size + c.size;
    combined.capacity = combined.size;
    combined.arr = new Record[combined.capacity];

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