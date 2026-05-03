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

// Preconditions: records sorted ascending by the field used in each search.
// Age: binary search first Age >= minAge, then linear scan while Age <= maxAge (e.g. 26–45).
void binarySearchByAge(const RecordArray& records, int minAge, int maxAge);

// Distance: binary search first dailyDistance > minDistance, then linear scan to end (e.g. > 15).
void binarySearchByDistance(const RecordArray& records, int minDistanceExclusive);

// Emission: binary search first monthlyCarbonEmission > threshold, then linear scan to end.
void binarySearchByEmission(const RecordArray& records, double emissionThreshold);

#endif