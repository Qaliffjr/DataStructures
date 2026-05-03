#include "SortedArraySort.hpp"
#include "ResidentArray.hpp"
#include <iostream>

bool isGreater(const Resident& a, const Resident& b, int sortBy) {
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

void insertionSortArray(ResidentArray& residents, int sortBy) {
    Resident* const arr = residents.arr;
    const int n = residents.size;

    for (int j = 1; j < n; ++j) {
        const Resident key = arr[j];
        int i = j - 1;

        while (i >= 0 && isGreater(arr[i], key, sortBy)) {
            arr[i + 1] = arr[i];
            --i;
        }

        arr[i + 1] = key;
    }
}

void displayArrayPreview(const ResidentArray& residents, int limit) {
    const int n = residents.size;
    const int count = (limit < n) ? limit : n;

    for (int i = 0; i < count; ++i) {
        const Resident& r = residents.arr[i];

        std::cout << i << ": Age=" << r.Age
            << "  dailyDistance=" << r.dailyDistance
            << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
    }
}

void displayLastNResidents(const ResidentArray& residents, int limit) {
    const int n = residents.size;
    if (n <= 0 || residents.arr == nullptr) {
        return;
    }
    const int count = (limit < n) ? limit : n;
    const int start = n - count;

    for (int i = start; i < n; ++i) {
        const Resident& r = residents.arr[i];

        std::cout << i << ": Age=" << r.Age
            << "  dailyDistance=" << r.dailyDistance
            << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
    }
}

bool validateSorted(const ResidentArray& residents, int sortBy) {
    const int n = residents.size;
    if (n <= 1 || residents.arr == nullptr) {
        return true;
    }

    for (int i = 0; i < n - 1; ++i) {
        const Resident& a = residents.arr[i];
        const Resident& b = residents.arr[i + 1];

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

int lowerBoundFirstAgeAtLeast(const ResidentArray& residents, int minAge) {
    const int n = residents.size;
    if (n <= 0 || residents.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (residents.arr[mid].Age >= minAge) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int lowerBoundFirstDistanceGreaterThan(const ResidentArray& residents, double minDistanceExclusive) {
    const int n = residents.size;
    if (n <= 0 || residents.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (residents.arr[mid].dailyDistance > minDistanceExclusive) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int lowerBoundFirstEmissionGreaterThan(const ResidentArray& residents, double threshold) {
    const int n = residents.size;
    if (n <= 0 || residents.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (residents.arr[mid].monthlyCarbonEmission > threshold) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void printResidentLine(int index, const Resident& r) {
    std::cout << index << ": Age=" << r.Age
        << "  dailyDistance=" << r.dailyDistance
        << "  monthlyCarbonEmission=" << r.monthlyCarbonEmission << '\n';
}

}  // namespace

void binarySearchByAge(const ResidentArray& residents, int minAge, int maxAge) {
    const int n = residents.size;
    std::cout << "\n--- binarySearchByAge (sorted by age) ---\n";
    std::cout << "Range: Age >= " << minAge << ", scan while Age <= " << maxAge << '\n';

    const int start = lowerBoundFirstAgeAtLeast(residents, minAge);
    std::cout << "Binary search: first index with Age >= " << minAge << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No residents found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        const Resident& r = residents.arr[i];
        if (r.Age > maxAge) {
            break;
        }
        printResidentLine(i, r);
        ++count;
    }
    std::cout << "Total in range: " << count << '\n';
}

void binarySearchByDistance(const ResidentArray& residents, double minDistanceExclusive) {
    const int n = residents.size;
    std::cout << "\n--- binarySearchByDistance (sorted by daily distance) ---\n";
    std::cout << "Query: dailyDistance > " << minDistanceExclusive << '\n';

    const int start = lowerBoundFirstDistanceGreaterThan(residents, minDistanceExclusive);
    std::cout << "Binary search: first index with dailyDistance > " << minDistanceExclusive
        << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No residents found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        printResidentLine(i, residents.arr[i]);
        ++count;
    }
    std::cout << "Total with dailyDistance > " << minDistanceExclusive << ": " << count << '\n';
}

void binarySearchByEmission(const ResidentArray& residents, double emissionThreshold) {
    const int n = residents.size;
    std::cout << "\n--- binarySearchByEmission (sorted by monthly carbon emission) ---\n";
    std::cout << "Query: monthlyCarbonEmission > " << emissionThreshold << '\n';

    const int start = lowerBoundFirstEmissionGreaterThan(residents, emissionThreshold);
    std::cout << "Binary search: first index with monthlyCarbonEmission > " << emissionThreshold
        << " is " << start << '\n';

    if (start >= n) {
        std::cout << "No residents found.\n";
        return;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        printResidentLine(i, residents.arr[i]);
        ++count;
    }
    std::cout << "Total with monthlyCarbonEmission > " << emissionThreshold << ": " << count << '\n';
}
