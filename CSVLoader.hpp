#pragma once
#include <string>
#include "ResidentArray.hpp"
#include "ResidentLinkedList.hpp"

int countLines(const std::string& filename);

void loadCSV(const std::string& filename,
    ResidentArray& arr,
    ResidentLinkedList& list);