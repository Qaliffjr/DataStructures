#ifndef SORTED_ARRAY_SORT_HPP
#define SORTED_ARRAY_SORT_HPP

#include "recordArray.hpp"

enum SortField {
    SORT_BY_AGE = 1,
    SORT_BY_DISTANCE = 2,
    SORT_BY_EMISSION = 3
};

bool isGreater(const Record& a, const Record& b, int sortBy);

void insertionSortArray(RecordArray& records, int sortBy);

void displayArrayPreview(const RecordArray& records, int limit);

void displayLastNRecords(const RecordArray& records, int limit);

bool validateSorted(const RecordArray& records, int sortBy);

void binarySearchByAge(const RecordArray& records, int minAge, int maxAge);

void binarySearchByDistance(const RecordArray& records, double minDistanceExclusive);

void binarySearchByEmission(const RecordArray& records, double emissionThreshold);

#endif
