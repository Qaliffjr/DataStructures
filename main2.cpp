#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "CSVParser.hpp"
#include "ResidentArray.hpp"
#include "SortedArraySort.hpp"

namespace {

bool loadRecordsFromCsv(const char* path, RecordArray& out) {
	ResidentArray src{};
	initArray(src);
	if (!loadCsvToArray(path, src)) {
		freeArray(src);
		return false;
	}

	delete[] out.arr;
	out.arr = new Record[src.size];
	out.size = src.size;
	out.capacity = src.size;

	for (int i = 0; i < src.size; ++i) {
		const Resident& r = src.data[i];
		out.arr[i] = Record{};
		out.arr[i].ID = r.residentID;
		out.arr[i].Age = r.age;
		out.arr[i].modeOfTransport = r.transportMode;
		out.arr[i].dailyDistance = static_cast<int>(std::lround(r.dailyDistance));
		out.arr[i].carbonEmission = r.emissionFactor;
		out.arr[i].monthlyFrequency = r.averageDaysPerMonth;
		out.arr[i].monthlyCarbonEmission = r.monthlyEmissions;
	}

	freeArray(src);
	return true;
}

void fillSampleRecords(RecordArray& out) {
	delete[] out.arr;
	out.size = 5;
	out.capacity = 5;
	out.arr = new Record[out.capacity];

	out.arr[0] = { "R001", 45, "Car", 20, 0.21, 22, 20.0 * 0.21 * 22.0 };
	out.arr[1] = { "R002", 18, "Bus", 12, 0.10, 20, 12.0 * 0.10 * 20.0 };
	out.arr[2] = { "R003", 32, "Bicycle", 5, 0.00, 18, 0.0 };
	out.arr[3] = { "R004", 60, "Car", 30, 0.21, 25, 30.0 * 0.21 * 25.0 };
	out.arr[4] = { "R005", 25, "Walking", 2, 0.00, 15, 0.0 };
}

void printMemoryEstimate(const RecordArray& records) {
	const int n = records.size;
	if (n <= 0 || records.arr == nullptr) {
		std::cout << "Memory (estimate): 0 bytes (empty array)\n";
		return;
	}

	std::size_t arrayBlock = static_cast<std::size_t>(n) * sizeof(Record);
	std::size_t stringHeap = 0;
	for (int i = 0; i < n; ++i) {
		stringHeap += records.arr[i].ID.capacity();
		stringHeap += records.arr[i].modeOfTransport.capacity();
	}
	const std::size_t pointerBlock = sizeof(RecordArray::arr) + sizeof(RecordArray::size)
		+ sizeof(RecordArray::capacity);
	const std::size_t total = pointerBlock + arrayBlock + stringHeap;

	std::cout << "Memory (rough estimate): " << total << " bytes\n";
	std::cout << "  struct array: " << arrayBlock << " bytes (" << n << " * sizeof(Record))\n";
	std::cout << "  string heap (capacity): " << stringHeap << " bytes\n";
}

void runTimedSort(const RecordArray& original, int sortBy, const char* sectionTitle, int previewLimit) {
	RecordArray work = copyArray(original);

	const auto t0 = std::chrono::steady_clock::now();
	insertionSortArray(work, sortBy);
	const auto t1 = std::chrono::steady_clock::now();

	const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
	const bool ok = validateSorted(work, sortBy);

	std::cout << '\n' << sectionTitle << '\n';
	std::cout << "Insertion sort time: " << std::fixed << std::setprecision(4) << ms << " ms\n"
		<< std::defaultfloat;
	std::cout << "Validation: " << (ok ? "PASSED" : "FAILED") << '\n';
	std::cout << "First " << previewLimit << " records:\n";
	displayArrayPreview(work, previewLimit);

	if (sortBy == SORT_BY_EMISSION) {
		std::cout << "Last " << previewLimit << " records:\n";
		displayLastNRecords(work, previewLimit);
	}

	freeArray(work);
}

void runBinarySearchDemos(const RecordArray& master) {
	std::cout << "\n========== Binary search (assignment-style) ==========\n";
	std::cout << "Each query uses a copy sorted by the matching key.\n";

	RecordArray byAge = copyArray(master);
	insertionSortArray(byAge, SORT_BY_AGE);
	if (validateSorted(byAge, SORT_BY_AGE)) {
		binarySearchByAge(byAge, 26, 45);
	} else {
		std::cout << "\nSkipping binarySearchByAge: array not sorted by age.\n";
	}
	freeArray(byAge);

	RecordArray byDistance = copyArray(master);
	insertionSortArray(byDistance, SORT_BY_DISTANCE);
	if (validateSorted(byDistance, SORT_BY_DISTANCE)) {
		binarySearchByDistance(byDistance, 15);
	} else {
		std::cout << "\nSkipping binarySearchByDistance: array not sorted by distance.\n";
	}
	freeArray(byDistance);

	RecordArray byEmission = copyArray(master);
	insertionSortArray(byEmission, SORT_BY_EMISSION);
	if (validateSorted(byEmission, SORT_BY_EMISSION)) {
		const double emissionThreshold = 50.0;
		binarySearchByEmission(byEmission, emissionThreshold);
	} else {
		std::cout << "\nSkipping binarySearchByEmission: array not sorted by emission.\n";
	}
	freeArray(byEmission);
}

}  // namespace

int main() {
	RecordArray master{};
	master.arr = nullptr;
	master.size = 0;
	master.capacity = 0;

	const char* csvPath = "dataset3-cityC.csv";
	if (!loadRecordsFromCsv(csvPath, master)) {
		std::cerr << "Note: could not load \"" << csvPath
			<< "\" (set working directory to the folder with the CSV). Using sample data.\n";
		fillSampleRecords(master);
	}

	std::cout << "Records loaded: " << master.size << "\n";
	printMemoryEstimate(master);

	std::cout << "\n--- Original (first 10) ---\n";
	displayArrayPreview(master, 10);

	runTimedSort(master, SORT_BY_AGE, "--- Sorted by Age ---", 10);
	runTimedSort(master, SORT_BY_DISTANCE, "--- Sorted by Daily Distance ---", 10);
	runTimedSort(master, SORT_BY_EMISSION, "--- Sorted by Monthly Carbon Emission ---", 10);

	runBinarySearchDemos(master);

	freeArray(master);
	return 0;
}
