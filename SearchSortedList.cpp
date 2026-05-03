#include "SortedArraySort.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

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

static void printSeparatorLine(std::ostream& out, int width) {
	out << std::string(static_cast<std::size_t>(width), '-') << '\n';
}

static const int kAgeMin[kMenuAgeGroupCount] = { 6, 18, 26, 46, 61 };
static const int kAgeMax[kMenuAgeGroupCount] = { 17, 25, 45, 60, 100 };
static const char* const kAgeLabel[kMenuAgeGroupCount] = {
	"Children & Teenagers (6-17)",
	"University Students / Young Adults (18-25)",
	"Working Adults - Early Career (26-45)",
	"Working Adults - Late Career (46-60)",
	"Senior Citizens / Retirees (61-100)"
};

RecordArray* recordDatasetByMenuId(int menuId, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	switch (menuId) {
	case 1:
		return &cityA;
	case 2:
		return &cityB;
	case 3:
		return &cityC;
	case 4:
		return &combined;
	default:
		return nullptr;
	}
}

const char* recordDatasetDisplayName(int menuId) {
	switch (menuId) {
	case 1:
		return "City A - Metropolitan";
	case 2:
		return "City B - University Town";
	case 3:
		return "City C - Suburban/Rural";
	case 4:
		return "Combined A + B + C";
	default:
		return "";
	}
}

const char* sortFieldDisplayName(int sortBy) {
	switch (sortBy) {
	case SORT_BY_AGE:
		return "Age";
	case SORT_BY_DISTANCE:
		return "Daily Distance";
	case SORT_BY_EMISSION:
		return "Monthly Carbon Emission";
	case SORT_BY_MODE:
		return "Mode of Transport";
	default:
		return "Unknown";
	}
}

bool ageGroupMenuBounds(int choice1to5, int& minAge, int& maxAge, const char*& label) {
	if (choice1to5 < 1 || choice1to5 > kMenuAgeGroupCount) {
		return false;
	}
	const int g = choice1to5 - 1;
	minAge = kAgeMin[g];
	maxAge = kAgeMax[g];
	label = kAgeLabel[g];
	return true;
}

const char* ageGroupMenuLabel(int choice1to5) {
	if (choice1to5 < 1 || choice1to5 > kMenuAgeGroupCount) {
		return "";
	}
	return kAgeLabel[choice1to5 - 1];
}

bool dailyDistanceMenuBounds(int choice1to3, double& minKm, double& maxKm, const char*& label) {
	switch (choice1to3) {
	case 1:
		minKm = 0.0;
		maxKm = 5.0;
		label = "0-5 km";
		return true;
	case 2:
		minKm = 6.0;
		maxKm = 15.0;
		label = "6-15 km";
		return true;
	case 3:
		minKm = 16.0;
		maxKm = std::numeric_limits<double>::max();
		label = "16+ km";
		return true;
	default:
		return false;
	}
}

double timedInsertionSort(RecordArray& work, int sortBy) {
	const auto t0 = std::chrono::high_resolution_clock::now();
	insertionSortArray(work, sortBy);
	const auto t1 = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

TimedSearchResult searchAgeGroupTimed(const RecordArray& source, int minAge, int maxAge, ResidentArray& out) {
	TimedSearchResult r{};
	RecordArray sorted = copyRecordArray(source);
	insertionSortArray(sorted, SORT_BY_AGE);
	r.sortValid = validateSorted(sorted, SORT_BY_AGE);
	if (!r.sortValid) {
		freeRecordArray(sorted);
		return r;
	}
	const auto t0 = std::chrono::high_resolution_clock::now();
	r.matchCount = binarySearchByAge(sorted, minAge, maxAge, out);
	const auto t1 = std::chrono::high_resolution_clock::now();
	r.searchMillis = std::chrono::duration<double, std::milli>(t1 - t0).count();
	freeRecordArray(sorted);
	return r;
}

TimedSearchResult searchTransportTimed(const RecordArray& source, const std::string& mode, ResidentArray& out) {
	TimedSearchResult r{};
	RecordArray sorted = copyRecordArray(source);
	insertionSortArray(sorted, SORT_BY_MODE);
	r.sortValid = validateSorted(sorted, SORT_BY_MODE);
	if (!r.sortValid) {
		freeRecordArray(sorted);
		return r;
	}
	const auto t0 = std::chrono::high_resolution_clock::now();
	r.matchCount = binarySearchByTransportMode(sorted, mode, out);
	const auto t1 = std::chrono::high_resolution_clock::now();
	r.searchMillis = std::chrono::duration<double, std::milli>(t1 - t0).count();
	freeRecordArray(sorted);
	return r;
}

TimedSearchResult searchDistanceRangeTimed(const RecordArray& source, double minKm, double maxKm, ResidentArray& out) {
	TimedSearchResult r{};
	RecordArray sorted = copyRecordArray(source);
	insertionSortArray(sorted, SORT_BY_DISTANCE);
	r.sortValid = validateSorted(sorted, SORT_BY_DISTANCE);
	if (!r.sortValid) {
		freeRecordArray(sorted);
		return r;
	}
	const auto t0 = std::chrono::high_resolution_clock::now();
	r.matchCount = searchByDailyDistanceRange(sorted, minKm, maxKm, out);
	const auto t1 = std::chrono::high_resolution_clock::now();
	r.searchMillis = std::chrono::duration<double, std::milli>(t1 - t0).count();
	freeRecordArray(sorted);
	return r;
}

void printMemoryUsageReport(const RecordArray& records, const char* datasetName) {
	const int n = records.size;
	std::cout << "\nDataset: " << (datasetName ? datasetName : "") << "\n";
	if (n <= 0 || records.arr == nullptr) {
		std::cout << "Memory estimate: 0 bytes\n";
		return;
	}

	std::size_t arrayBlock = static_cast<std::size_t>(n) * sizeof(Record);
	std::size_t stringHeap = 0;
	for (int i = 0; i < n; ++i) {
		stringHeap += records.arr[i].ID.capacity();
		stringHeap += records.arr[i].modeOfTransport.capacity();
	}
	const std::size_t total = sizeof(RecordArray) + arrayBlock + stringHeap;
	std::cout << "Memory estimate: " << total << " bytes\n";
	std::cout << "  Struct array: " << arrayBlock << " bytes\n";
	std::cout << "  String heap: " << stringHeap << " bytes\n";
}

void printAgeGroupHistogram(const RecordArray& arr, const char* datasetTitle) {
	std::cout << "\n\n"
		<< std::setfill('-') << std::setw(60) << "-" << "\n"
		<< std::setfill(' ')
		<< datasetTitle << "\n"
		<< std::setfill('-') << std::setw(60) << "-" << "\n";
	for (int g = 0; g < kMenuAgeGroupCount; ++g) {
		int c = 0;
		for (int i = 0; i < arr.size; ++i) {
			const int a = arr.arr[i].Age;
			if (a >= kAgeMin[g] && a <= kAgeMax[g]) {
				++c;
			}
		}
		std::cout << "  " << kAgeLabel[g] << ": " << c << "\n";
	}
}

void printInsertionSortReport(const RecordArray& source, int sortBy, const char* datasetName) {
	RecordArray work = copyRecordArray(source);

	const auto t0 = std::chrono::high_resolution_clock::now();
	insertionSortArray(work, sortBy);
	const auto t1 = std::chrono::high_resolution_clock::now();
	const double elapsed = std::chrono::duration<double, std::milli>(t1 - t0).count();

	std::cout << "\n";
	printSeparatorLine(std::cout, 72);
	std::cout << "SORTED ARRAY - INSERTION SORT\n";
	std::cout << "Dataset : " << (datasetName ? datasetName : "") << "\n";
	std::cout << "Sort By : " << sortFieldDisplayName(sortBy) << "\n";
	printSeparatorLine(std::cout, 72);

	std::cout << "Insertion sort time: " << std::fixed << std::setprecision(4) << elapsed << " ms\n"
		<< std::defaultfloat;

	std::cout << "Validation: " << (validateSorted(work, sortBy) ? "PASSED" : "FAILED") << "\n";

	std::cout << "\nFirst 10 records:\n";
	displayArrayPreview(work, 10);

	if (sortBy == SORT_BY_EMISSION) {
		std::cout << "\nLast 10 records:\n";
		displayLastNRecords(work, 10);
	}

	freeRecordArray(work);
}

static void printProcessTimeLine(double ms) {
	std::cout << "\n  [Process time: " << std::fixed << std::setprecision(4) << ms << " ms]\n"
		<< std::defaultfloat;
}

void runBinarySearchDemoWithIO(const RecordArray& original, const char* datasetName) {
	std::cout << "\n";
	printSeparatorLine(std::cout, 72);
	std::cout << "SORTED ARRAY - BINARY SEARCH (results in ResidentArray)\n";
	std::cout << "Dataset : " << (datasetName ? datasetName : "") << "\n";
	printSeparatorLine(std::cout, 72);

	ResidentArray matches{};
	initArray(matches);

	RecordArray byAge = copyRecordArray(original);
	insertionSortArray(byAge, SORT_BY_AGE);
	if (!validateSorted(byAge, SORT_BY_AGE)) {
		std::cout << "\nAge sort validation FAILED.\n";
		freeRecordArray(byAge);
		freeArray(matches);
		return;
	}

	std::cout << "\n--- Search by age (26-45) ---\n";
	auto ageStart = std::chrono::high_resolution_clock::now();
	const int nAge = binarySearchByAge(byAge, 26, 45, matches);
	auto ageEnd = std::chrono::high_resolution_clock::now();
	printProcessTimeLine(std::chrono::duration<double, std::milli>(ageEnd - ageStart).count());
	std::cout << "Matches: " << nAge << "\nFirst 10 results:\n";
	displayResidentArrayPreview(matches, 10);
	freeRecordArray(byAge);

	RecordArray byDistance = copyRecordArray(original);
	insertionSortArray(byDistance, SORT_BY_DISTANCE);
	if (!validateSorted(byDistance, SORT_BY_DISTANCE)) {
		std::cout << "\nDistance sort validation FAILED.\n";
		freeRecordArray(byDistance);
		freeArray(matches);
		return;
	}

	std::cout << "\n--- Search by daily distance (distance > 15 km) ---\n";
	auto dStart = std::chrono::high_resolution_clock::now();
	const int nDist = binarySearchByDistance(byDistance, 15.0, matches);
	auto dEnd = std::chrono::high_resolution_clock::now();
	printProcessTimeLine(std::chrono::duration<double, std::milli>(dEnd - dStart).count());
	std::cout << "Matches: " << nDist << "\nFirst 10 results:\n";
	displayResidentArrayPreview(matches, 10);
	freeRecordArray(byDistance);

	RecordArray byMode = copyRecordArray(original);
	insertionSortArray(byMode, SORT_BY_MODE);
	if (!validateSorted(byMode, SORT_BY_MODE)) {
		std::cout << "\nMode sort validation FAILED.\n";
		freeRecordArray(byMode);
		freeArray(matches);
		return;
	}

	std::cout << "\n--- Search by mode of transport ---\n";
	for (int m = 0; m < NUM_TRANSPORT_MODES; ++m) {
		std::cout << "  " << (m + 1) << ". " << TRANSPORT_MODE_NAMES[m] << "\n";
	}
	std::cout << "Enter mode number (1-" << NUM_TRANSPORT_MODES << "): ";
	int modeChoice = 0;
	std::cin >> modeChoice;

	if (modeChoice < 1 || modeChoice > NUM_TRANSPORT_MODES) {
		std::cout << "Invalid mode.\n";
	} else {
		const std::string modeStr(TRANSPORT_MODE_NAMES[modeChoice - 1]);
		auto mStart = std::chrono::high_resolution_clock::now();
		const int nMode = binarySearchByTransportMode(byMode, modeStr, matches);
		auto mEnd = std::chrono::high_resolution_clock::now();
		printProcessTimeLine(std::chrono::duration<double, std::milli>(mEnd - mStart).count());
		std::cout << "Mode: " << modeStr << "\nMatches: " << nMode << "\n";
		std::cout << "First 10 results:\n";
		displayResidentArrayPreview(matches, 10);
		std::cout << "Last 10 results:\n";
		displayResidentArrayLastN(matches, 10);
	}

	freeRecordArray(byMode);
	freeArray(matches);
}
