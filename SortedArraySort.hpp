#ifndef SORTED_ARRAY_SORT_HPP
#define SORTED_ARRAY_SORT_HPP
#include <string>
#include "recordArray.hpp"

struct ResidentArray;

enum SortField {
	SORT_BY_AGE = 1,
	SORT_BY_DISTANCE = 2,
	SORT_BY_EMISSION = 3,
	SORT_BY_MODE = 4
};

bool isGreater(const Record& a, const Record& b, int sortBy);

void insertionSortArray(RecordArray& records, int sortBy);

bool validateSorted(const RecordArray& records, int sortBy);

// Binary search + linear scan; fills `out` (cleared first). Returns number of records appended.
// Preconditions: `records` sorted ascending by the matching sort key.
int binarySearchByAge(const RecordArray& records, int minAge, int maxAge, ResidentArray& out);

int binarySearchByDistance(const RecordArray& records, double minDistanceExclusive, ResidentArray& out);

// Sorted by modeOfTransport (lexicographic). Finds exact `mode` string (e.g. "Bicycle", "School Bus").
int binarySearchByTransportMode(const RecordArray& records, const std::string& mode, ResidentArray& out);

// Inclusive distance range [minKm, maxKm]. Precondition: sorted by daily distance ascending.
int searchByDailyDistanceRange(const RecordArray& records, double minKmInclusive, double maxKmInclusive, ResidentArray& out);

#endif
