#pragma once
#include <string>
#include "recordArray.hpp"
#include "recordLinkedList.hpp"

int countLines(const std::string& filename);

void loadCSV(const std::string& filename,
    RecordArray& arr,
    RecordLinkedList& list);