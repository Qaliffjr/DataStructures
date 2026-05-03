#ifndef RECORD_ARRAY_UTILS_HPP
#define RECORD_ARRAY_UTILS_HPP

#include <string>
#include "recordArray.hpp"
#include "recordLinkedList.hpp"
#include "ResidentArray.hpp"

void initRecordArray(RecordArray& arr, int capacity);
void freeRecordArray(RecordArray& arr);
RecordArray copyRecordArray(const RecordArray& source);

void initRecordLinkedList(RecordLinkedList& list);
void freeRecordLinkedList(RecordLinkedList& list);

bool loadDataset(
    const std::string& filename,
    RecordArray& arr,
    RecordLinkedList& list
);

RecordArray combineArrays(
    const RecordArray& a,
    const RecordArray& b,
    const RecordArray& c
);

void recordToResident(const Record& r, Resident& out);

void displayArrayPreview(const RecordArray& records, int limit);
void displayLastNRecords(const RecordArray& records, int limit);
void displayResidentArrayPreview(const ResidentArray& residents, int limit);
void displayResidentArrayLastN(const ResidentArray& residents, int limit);

#endif
