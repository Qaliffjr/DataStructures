#include "SortedArraySort.hpp"
#include <iostream>

bool isGreater(const Record& a, const Record& b, int sortBy) {
    switch (sortBy) {
    case SORT_BY_AGE:
        return a.Age > b.Age;

    case SORT_BY_DISTANCE:
        return a.dailyDistance > b.dailyDistance;

    case SORT_BY_EMISSION:
        return a.monthlyCarbonEmission > b.monthlyCarbonEmission;

    default:
        return false;
    }
}

void insertionSortArray(RecordArray& records, int sortBy) {
    Record* const arr = records.arr;
    const int n = records.size;

    for (int j = 1; j < n; ++j) {
        const Record key = arr[j];
        int i = j - 1;

        while (i >= 0 && isGreater(arr[i], key, sortBy)) {
            arr[i + 1] = arr[i];
            --i;
        }

        arr[i + 1] = key;
    }
}

void displayArrayPreview(const RecordArray& records, int limit) {
    const int n = records.size;
    const int count = (limit < n) ? limit : n;

    for (int i = 0; i < count; ++i) {
        const Record& r = records.arr[i];

        std::cout << i << ": Age=" << r.Age
            << "  dailyDistance=" << r.dailyDistance
            << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
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

        std::cout << i << ": Age=" << r.Age
            << "  dailyDistance=" << r.dailyDistance
            << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
    }
}

bool validateSorted(const RecordArray& records, int sortBy) {
    const int n = records.size;
    if (n <= 1 || records.arr == nullptr) {
        return true;
    }

    for (int i = 0; i < n - 1; ++i) {
        const Record& a = records.arr[i];
        const Record& b = records.arr[i + 1];

        switch (sortBy) {
        case SORT_BY_AGE:
            if (a.Age > b.Age) {
                return false;
            }
            break;
        case SORT_BY_DISTANCE:
            if (a.dailyDistance > b.dailyDistance) {
                return false;
            }
            break;
        case SORT_BY_EMISSION:
            if (a.monthlyCarbonEmission > b.monthlyCarbonEmission) {
                return false;
            }
            break;
        default:
            return false;
        }
    }
    return true;
}

namespace {

int lowerBoundFirstAgeAtLeast(const RecordArray& records, int minAge) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (records.arr[mid].Age >= minAge) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int lowerBoundFirstDistanceGreaterThan(const RecordArray& records, int minDistanceExclusive) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (records.arr[mid].dailyDistance > minDistanceExclusive) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int lowerBoundFirstEmissionGreaterThan(const RecordArray& records, double threshold) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (records.arr[mid].monthlyCarbonEmission > threshold) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void printRecordLine(int index, const Record& r) {
    std::cout << index << ": Age=" << r.Age
        << "  dailyDistance=" << r.dailyDistance
        << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
}

}  // namespace

void binarySearchByAge(const RecordArray& records, int minAge, int maxAge) {
    const int n = records.size;
    std::cout << "\n--- binarySearchByAge (sorted by age) ---\n";
    std::cout << "Range: Age >= " << minAge << ", scan while Age <= " << maxAge << '\n';

    const int start = lowerBoundFirstAgeAtLeast(records, minAge);
    std::cout << "Binary search: first index with Age >= " << minAge << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No records found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        const Record& r = records.arr[i];
        if (r.Age > maxAge) {
            break;
        }
        printRecordLine(i, r);
        ++count;
    }
    std::cout << "Total in range: " << count << '\n';
}

void binarySearchByDistance(const RecordArray& records, int minDistanceExclusive) {
    const int n = records.size;
    std::cout << "\n--- binarySearchByDistance (sorted by daily distance) ---\n";
    std::cout << "Query: dailyDistance > " << minDistanceExclusive << '\n';

    const int start = lowerBoundFirstDistanceGreaterThan(records, minDistanceExclusive);
    std::cout << "Binary search: first index with dailyDistance > " << minDistanceExclusive
        << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No records found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        printRecordLine(i, records.arr[i]);
        ++count;
    }
    std::cout << "Total with dailyDistance > " << minDistanceExclusive << ": " << count << '\n';
}

void binarySearchByEmission(const RecordArray& records, double emissionThreshold) {
    const int n = records.size;
    std::cout << "\n--- binarySearchByEmission (sorted by monthly carbon emission) ---\n";
    std::cout << "Query: monthlyCarbonEmission > " << emissionThreshold << '\n';

    const int start = lowerBoundFirstEmissionGreaterThan(records, emissionThreshold);
    std::cout << "Binary search: first index with monthlyCarbonEmission > " << emissionThreshold
        << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No records found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        printRecordLine(i, records.arr[i]);
        ++count;
    }
    std::cout << "Total with monthlyCarbonEmission > " << emissionThreshold << ": " << count << '\n';
}