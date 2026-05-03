#ifndef SORTED_ARRAY_SORT_HPP
#define SORTED_ARRAY_SORT_HPP

#include "ResidentArray.hpp"

enum SortField {
    SORT_BY_AGE = 1,
    SORT_BY_DISTANCE = 2,
    SORT_BY_EMISSION = 3
};

bool isGreater(const Resident& a, const Resident& b, int sortBy);

void insertionSortArray(ResidentArray& resident, int sortBy);

void displayArrayPreview(const ResidentArray& resident, int limit);
void displayLastNRecords(const ResidentArray& resident, int limit);

bool validateSorted(const ResidentArray& resident, int sortBy);

#endif
