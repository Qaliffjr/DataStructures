#include "RecordArrayUtils.hpp"
#include "CSVLoader.hpp"

#include <cstring>
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

void recordToResident(const Record& r, Resident& out) {
    out = Resident{};
#if defined(_MSC_VER)
    strncpy_s(out.residentID, sizeof(out.residentID), r.ID.c_str(), _TRUNCATE);
    strncpy_s(out.transportMode, sizeof(out.transportMode), r.modeOfTransport.c_str(), _TRUNCATE);
#else
    std::strncpy(out.residentID, r.ID.c_str(), sizeof(out.residentID) - 1);
    out.residentID[sizeof(out.residentID) - 1] = '\0';
    std::strncpy(out.transportMode, r.modeOfTransport.c_str(), sizeof(out.transportMode) - 1);
    out.transportMode[sizeof(out.transportMode) - 1] = '\0';
#endif
    out.age = r.Age;
    out.dailyDistance = r.dailyDistance;
    out.emissionFactor = r.carbonEmission;
    out.averageDaysPerMonth = r.monthlyFrequency;
    out.monthlyEmissions = r.monthlyCarbonEmission;
}

void displayArrayPreview(const RecordArray& records, int limit) {
    const int n = records.size;
    const int count = (limit < n) ? limit : n;

    for (int i = 0; i < count; ++i) {
        const Record& r = records.arr[i];
        std::cout << i << ": ID=" << r.ID << " Age=" << r.Age
            << " mode=" << r.modeOfTransport
            << " dailyDistance=" << r.dailyDistance
            << " monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
    }
}

void displayLastNRecords(const RecordArray& records, int limit) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return;
    }
    const int count = (limit < n) ? limit : n;
    const int start = n - count;

    for (int i = start; i < n; ++i) {
        const Record& r = records.arr[i];
        std::cout << i << ": ID=" << r.ID << " Age=" << r.Age
            << " mode=" << r.modeOfTransport
            << " dailyDistance=" << r.dailyDistance
            << " monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
    }
}

void displayResidentArrayPreview(const ResidentArray& residents, int limit) {
    const int n = residents.size;
    if (n <= 0 || residents.data == nullptr) {
        return;
    }
    const int count = (limit < n) ? limit : n;
    for (int i = 0; i < count; ++i) {
        const Resident& r = residents.data[i];
        std::cout << i << ": ID=" << r.residentID << " Age=" << r.age
            << " mode=" << r.transportMode
            << " dailyDistance=" << r.dailyDistance
            << " monthlyEmissions=" << r.monthlyEmissions << '\n';
    }
}

void displayResidentArrayLastN(const ResidentArray& residents, int limit) {
    const int n = residents.size;
    if (n <= 0 || residents.data == nullptr) {
        return;
    }
    const int count = (limit < n) ? limit : n;
    const int start = n - count;
    for (int i = start; i < n; ++i) {
        const Resident& r = residents.data[i];
        std::cout << i << ": ID=" << r.residentID << " Age=" << r.age
            << " mode=" << r.transportMode
            << " dailyDistance=" << r.dailyDistance
            << " monthlyEmissions=" << r.monthlyEmissions << '\n';
    }
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
