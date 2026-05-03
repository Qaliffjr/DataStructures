#include "SortedArraySort.hpp"

#include "RecordArrayUtils.hpp"
#include "ResidentArray.hpp"

bool isGreater(const Record& a, const Record& b, int sortBy) {
    switch (sortBy) {
    case SORT_BY_AGE:
        return a.Age > b.Age;

    case SORT_BY_DISTANCE:
        return a.dailyDistance > b.dailyDistance;

    case SORT_BY_EMISSION:
        return a.monthlyCarbonEmission > b.monthlyCarbonEmission;

    case SORT_BY_MODE:
        return a.modeOfTransport > b.modeOfTransport;

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
        case SORT_BY_MODE:
            if (a.modeOfTransport > b.modeOfTransport) {
                return false;
            }
            break;
        default:
            return false;
        }
    }
    return true;
}

static int lowerBoundFirstAgeAtLeast(const RecordArray& records, int minAge) {
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

static int lowerBoundFirstDistanceAtLeast(const RecordArray& records, double minKmInclusive) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (records.arr[mid].dailyDistance >= minKmInclusive) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

static int lowerBoundFirstDistanceGreaterThan(const RecordArray& records, double minDistanceExclusive) {
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

static int lowerBoundFirstModeAtLeast(const RecordArray& records, const std::string& mode) {
    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (records.arr[mid].modeOfTransport >= mode) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

static bool appendMatch(ResidentArray& out, const Record& r) {
    Resident tmp{};
    recordToResident(r, tmp);
    return pushBack(out, tmp);
}

int binarySearchByAge(const RecordArray& records, int minAge, int maxAge, ResidentArray& out) {
    clearResidentArray(out);

    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }

    const int start = lowerBoundFirstAgeAtLeast(records, minAge);
    if (start >= n) {
        return 0;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        const Record& r = records.arr[i];
        if (r.Age > maxAge) {
            break;
        }
        if (!appendMatch(out, r)) {
            break;
        }
        ++count;
    }
    return count;
}

int binarySearchByDistance(const RecordArray& records, double minDistanceExclusive, ResidentArray& out) {
    clearResidentArray(out);

    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }

    const int start = lowerBoundFirstDistanceGreaterThan(records, minDistanceExclusive);
    if (start >= n) {
        return 0;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        if (!appendMatch(out, records.arr[i])) {
            break;
        }
        ++count;
    }
    return count;
}

int searchByDailyDistanceRange(const RecordArray& records, double minKmInclusive, double maxKmInclusive, ResidentArray& out) {
    clearResidentArray(out);

    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }

    const int start = lowerBoundFirstDistanceAtLeast(records, minKmInclusive);
    if (start >= n) {
        return 0;
    }

    int count = 0;
    for (int i = start; i < n; ++i) {
        if (records.arr[i].dailyDistance > maxKmInclusive) {
            break;
        }
        if (!appendMatch(out, records.arr[i])) {
            break;
        }
        ++count;
    }
    return count;
}

int binarySearchByTransportMode(const RecordArray& records, const std::string& mode, ResidentArray& out) {
    clearResidentArray(out);

    const int n = records.size;
    if (n <= 0 || records.arr == nullptr) {
        return 0;
    }

    const int start = lowerBoundFirstModeAtLeast(records, mode);
    if (start >= n || records.arr[start].modeOfTransport != mode) {
        return 0;
    }

    int count = 0;
    for (int i = start; i < n && records.arr[i].modeOfTransport == mode; ++i) {
        if (!appendMatch(out, records.arr[i])) {
            break;
        }
        ++count;
    }
    return count;
}
