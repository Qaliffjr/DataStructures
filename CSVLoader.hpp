#ifndef CSV_LOADER_HPP
#define CSV_LOADER_HPP

#include <string>
#include "ResidentArray.hpp"
#include "ResidentLinkedList.hpp"

int countLines(const std::string& filename);

void loadCSV(const std::string& filename,
    ResidentArray& arr,
    ResidentLinkedList& list);

#endif