#pragma once
#include <string>
#include "record.hpp"

struct RecordArray {
    Record* arr;
    int size;
    int capacity;
};
