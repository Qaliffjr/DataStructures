#include "menu.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

#include "RecordArrayUtils.hpp"
#include "ResidentArray.hpp"
#include "SortedArraySort.hpp"

using namespace std;

// ---------------------------------------------------------------------------
// menu.cpp — prompts, navigation, and wiring only. Algorithms and experiment
// reports live in SortedArraySort.cpp / RecordArrayUtils.
// ---------------------------------------------------------------------------

static void printTitle(const string& text, int width = 60) {
	const int padding = static_cast<int>(width - text.length()) / 2;
	cout << setfill('=') << setw(width) << "=" << "\n"
		<< setfill(' ')
		<< setw(padding + static_cast<int>(text.length())) << text << "\n"
		<< setfill('=') << setw(width) << "=" << "\n";
}

static void printSubtitle(const string& text, int width = 60) {
	const int padding = static_cast<int>(width - text.length()) / 2;
	cout << "\n\n"
		<< setfill('-') << setw(width) << "-" << "\n"
		<< setfill(' ')
		<< setw(padding + static_cast<int>(text.length())) << text << "\n"
		<< setfill('-') << setw(width) << "-" << "\n";
}

static void displayProcessTime(chrono::duration<double, milli> ms) {
	cout << "\n  [Process time: " << fixed << setprecision(4) << ms.count() << " ms]\n"
		<< defaultfloat;
}

static void waitToReturn() {
	cout << "Press Enter to return to the main menu...";
	cin.ignore();
	cin.get();
	cout << "\n\n\n";
}

static int selectAgeGroup() {
	int group;
	cout << "\nSelect age group:\n";
	for (int g = 0; g < kMenuAgeGroupCount; ++g) {
		cout << "  " << (g + 1) << ". " << ageGroupMenuLabel(g + 1) << "\n";
	}
	cout << "  0. Return\n"
		<< "Enter choice: ";
	cin >> group;
	return group;
}

static int selectTransportModeUnified() {
	int mode;
	cout << "\nSelect transport mode:\n";
	for (int m = 0; m < NUM_TRANSPORT_MODES; ++m) {
		cout << "  " << (m + 1) << ". " << TRANSPORT_MODE_NAMES[m] << "\n";
	}
	cout << "  0. Return\n"
		<< "Enter choice: ";
	cin >> mode;
	return mode;
}

static int selectDailyDistanceGroup() {
	int group;
	cout << "\nSelect daily distance band:\n"
		<< "  1. 0-5 km\n"
		<< "  2. 6-15 km\n"
		<< "  3. 16+ km\n"
		<< "  0. Return\n"
		<< "Enter choice: ";
	cin >> group;
	return group;
}

static int selectDataSet() {
	int dataSet;
	cout << "\nSelect dataset:\n"
		<< "  1. City A - Metropolitan\n"
		<< "  2. City B - University Town\n"
		<< "  3. City C - Suburban/Rural\n"
		<< "  4. Combined A + B + C\n"
		<< "  0. Return\n"
		<< "Enter choice: ";
	cin >> dataSet;
	return dataSet;
}

static int selectDataContainer() {
	int container;
	cout << "\nSelect data container:\n"
		<< "  1. Array (RecordArray + algorithms)\n"
		<< "  2. Linked list (not implemented)\n"
		<< "  0. Return\n"
		<< "Enter choice: ";
	cin >> container;
	return container;
}

static int selectSortField() {
	int sortBy;
	cout << "\nSelect sorting field:\n"
		<< "  1. Age\n"
		<< "  2. Daily Distance\n"
		<< "  3. Monthly Carbon Emission\n"
		<< "  4. Mode of Transport\n"
		<< "  0. Return\n"
		<< "Enter choice: ";
	cin >> sortBy;
	return sortBy;
}

static void runArraySortingExperiment(
	RecordArray& cityA,
	RecordArray& cityB,
	RecordArray& cityC,
	RecordArray& combined,
	int dataSet,
	bool showResult
) {
	RecordArray* selected = recordDatasetByMenuId(dataSet, cityA, cityB, cityC, combined);

	if (selected == nullptr || selected->arr == nullptr || selected->size <= 0) {
		cout << "Invalid or empty dataset.\n";
		return;
	}

	const int sortBy = selectSortField();

	if (sortBy == 0) {
		cout << "Returning.\n";
		return;
	}

	if (sortBy != SORT_BY_AGE && sortBy != SORT_BY_DISTANCE && sortBy != SORT_BY_EMISSION && sortBy != SORT_BY_MODE) {
		cout << "Invalid sorting field.\n";
		return;
	}

	if (!showResult) {
		RecordArray work = copyRecordArray(*selected);
		const double ms = timedInsertionSort(work, sortBy);
		cout << "\nSorted " << selected->size << " records.\n";
		displayProcessTime(chrono::duration<double, milli>(ms));
		cout << "Validation: " << (validateSorted(work, sortBy) ? "PASSED" : "FAILED") << "\n";
		freeRecordArray(work);
		return;
	}

	printInsertionSortReport(*selected, sortBy, recordDatasetDisplayName(dataSet));
}

static void runArrayAgeSearch(
	RecordArray& cityA,
	RecordArray& cityB,
	RecordArray& cityC,
	RecordArray& combined,
	int dataSet,
	int ageGroup,
	bool showResult
) {
	int minAge = 0;
	int maxAge = 0;
	const char* lab = nullptr;
	if (!ageGroupMenuBounds(ageGroup, minAge, maxAge, lab)) {
		cout << "Invalid age group.\n";
		return;
	}

	RecordArray* selected = recordDatasetByMenuId(dataSet, cityA, cityB, cityC, combined);
	if (selected == nullptr || selected->size <= 0) {
		cout << "Invalid or empty dataset.\n";
		return;
	}

	ResidentArray matches{};
	initArray(matches);

	const TimedSearchResult r = searchAgeGroupTimed(*selected, minAge, maxAge, matches);

	cout << "\nAge search: " << lab << " (" << minAge << "-" << maxAge << ")\n";
	cout << "Matches: " << r.matchCount << "\n";
	if (!r.sortValid) {
		cout << "Sort validation FAILED.\n";
		freeArray(matches);
		return;
	}
	if (showResult) {
		displayProcessTime(chrono::duration<double, milli>(r.searchMillis));
		cout << "First 15 results:\n";
		displayResidentArrayPreview(matches, 15);
	}

	freeArray(matches);
}

static void runArrayTransportSearch(
	RecordArray& cityA,
	RecordArray& cityB,
	RecordArray& cityC,
	RecordArray& combined,
	int dataSet,
	int modeChoice,
	bool showResult
) {
	if (modeChoice < 1 || modeChoice > NUM_TRANSPORT_MODES) {
		cout << "Invalid mode.\n";
		return;
	}

	RecordArray* selected = recordDatasetByMenuId(dataSet, cityA, cityB, cityC, combined);
	if (selected == nullptr || selected->size <= 0) {
		cout << "Invalid or empty dataset.\n";
		return;
	}

	const string modeStr(TRANSPORT_MODE_NAMES[modeChoice - 1]);

	ResidentArray matches{};
	initArray(matches);

	const TimedSearchResult r = searchTransportTimed(*selected, modeStr, matches);

	cout << "\nTransport search: " << modeStr << "\nMatches: " << r.matchCount << "\n";
	if (!r.sortValid) {
		cout << "Sort validation FAILED.\n";
		freeArray(matches);
		return;
	}
	if (showResult) {
		displayProcessTime(chrono::duration<double, milli>(r.searchMillis));
		cout << "First 15 results:\n";
		displayResidentArrayPreview(matches, 15);
	}

	freeArray(matches);
}

static void runArrayDistanceBandSearch(
	RecordArray& cityA,
	RecordArray& cityB,
	RecordArray& cityC,
	RecordArray& combined,
	int dataSet,
	int dGroup,
	bool showResult
) {
	double minKm = 0.0;
	double maxKm = 0.0;
	const char* label = nullptr;

	if (!dailyDistanceMenuBounds(dGroup, minKm, maxKm, label)) {
		cout << "Invalid distance group.\n";
		return;
	}

	RecordArray* selected = recordDatasetByMenuId(dataSet, cityA, cityB, cityC, combined);
	if (selected == nullptr || selected->size <= 0) {
		cout << "Invalid or empty dataset.\n";
		return;
	}

	ResidentArray matches{};
	initArray(matches);

	const TimedSearchResult r = searchDistanceRangeTimed(*selected, minKm, maxKm, matches);

	cout << "\nDistance band: " << label << "\nMatches: " << r.matchCount << "\n";
	if (!r.sortValid) {
		cout << "Sort validation FAILED.\n";
		freeArray(matches);
		return;
	}
	if (showResult) {
		displayProcessTime(chrono::duration<double, milli>(r.searchMillis));
		cout << "First 15 results:\n";
		displayResidentArrayPreview(matches, 15);
	}

	freeArray(matches);
}

static void searchingCriteriaMenu(
	int container,
	int dataSet,
	bool showResult,
	RecordArray& cityA,
	RecordArray& cityB,
	RecordArray& cityC,
	RecordArray& combined
) {
	if (container == 2) {
		cout << "Linked-list search is not implemented in this build.\n";
		return;
	}

	int nav;
	cout << "\nSelect search type:\n"
		<< "  1. Search by age group\n"
		<< "  2. Search by mode of transport\n"
		<< "  3. Search by daily distance band\n"
		<< "  0. Return\n"
		<< "Enter choice: ";
	cin >> nav;

	if (nav == 0) {
		return;
	}

	switch (nav) {
	case 1: {
		const int aGroup = selectAgeGroup();
		if (aGroup == 0) {
			return;
		}
		runArrayAgeSearch(cityA, cityB, cityC, combined, dataSet, aGroup, showResult);
		break;
	}
	case 2: {
		const int mode = selectTransportModeUnified();
		if (mode == 0) {
			return;
		}
		runArrayTransportSearch(cityA, cityB, cityC, combined, dataSet, mode, showResult);
		break;
	}
	case 3: {
		const int dGroup = selectDailyDistanceGroup();
		if (dGroup == 0) {
			return;
		}
		runArrayDistanceBandSearch(cityA, cityB, cityC, combined, dataSet, dGroup, showResult);
		break;
	}
	default:
		cout << "Invalid choice.\n";
	}
}

static void emissionMenu() {
	int nav;
	while (true) {
		printSubtitle("Carbon Emission Analysis");
		cout << "Select option:\n"
			<< "  1. Compare by age group (record counts)\n"
			<< "  2. Placeholder - mode comparison\n"
			<< "  3. Placeholder - distance comparison\n"
			<< "  0. Return\n"
			<< "Enter choice: ";
		cin >> nav;
		switch (nav) {
		case 1:
			cout << "Use main menu item 1 for per-city age breakdown, or extend here.\n";
			waitToReturn();
			return;
		case 2:
		case 3:
			cout << "Not implemented yet.\n";
			waitToReturn();
			return;
		case 0:
			return;
		default:
			cout << "Invalid choice.\n";
		}
	}
}

static void sortingMenu(bool display, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	while (true) {
		printSubtitle("Sorting Experiment");
		int nav;
		cout << "Select container:\n"
			<< "  1. Array\n"
			<< "  2. Linked list (not implemented)\n"
			<< "  0. Return\n"
			<< "Enter choice: ";
		cin >> nav;

		if (nav == 0) {
			return;
		}
		if (nav == 2) {
			cout << "Linked list sorting is not implemented.\n";
			waitToReturn();
			continue;
		}
		if (nav != 1) {
			cout << "Invalid choice.\n";
			continue;
		}

		const int dataSet = selectDataSet();
		if (dataSet == 0) {
			return;
		}
		if (dataSet < 1 || dataSet > 4) {
			cout << "Invalid dataset.\n";
			continue;
		}

		runArraySortingExperiment(cityA, cityB, cityC, combined, dataSet, display);
		waitToReturn();
		return;
	}
}

static void searchingMenu(bool display, RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	while (true) {
		printSubtitle("Searching Experiment");
		const int container = selectDataContainer();
		if (container == 0) {
			return;
		}

		const int dataSet = selectDataSet();
		if (dataSet == 0) {
			return;
		}
		if (dataSet < 1 || dataSet > 4) {
			cout << "Invalid dataset.\n";
			continue;
		}

		searchingCriteriaMenu(container, dataSet, display, cityA, cityB, cityC, combined);
		waitToReturn();
		return;
	}
}

static void sortedArrayToolsMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	while (true) {
		printSubtitle("Sorted Array Tools (CSV datasets)");
		int choice;
		cout << "  1. Memory estimate\n"
			<< "  2. Insertion sort experiment\n"
			<< "  3. Binary search demo (age / distance / mode)\n"
			<< "  4. Show original first 10 records\n"
			<< "  0. Return\n"
			<< "Enter choice: ";
		cin >> choice;

		if (choice == 0) {
			return;
		}

		const int ds = (choice >= 1 && choice <= 4) ? selectDataSet() : 0;
		if (choice != 0 && ds == 0) {
			continue;
		}
		if (ds < 1 || ds > 4) {
			cout << "Invalid dataset.\n";
			continue;
		}

		RecordArray* selected = recordDatasetByMenuId(ds, cityA, cityB, cityC, combined);
		if (selected == nullptr || selected->size <= 0) {
			cout << "Invalid or empty dataset.\n";
			continue;
		}

		if (choice == 1) {
			printMemoryUsageReport(*selected, recordDatasetDisplayName(ds));
		} else if (choice == 2) {
			const int sortBy = selectSortField();
			if (sortBy == 0) {
				continue;
			}
			if (sortBy != SORT_BY_AGE && sortBy != SORT_BY_DISTANCE && sortBy != SORT_BY_EMISSION && sortBy != SORT_BY_MODE) {
				cout << "Invalid sort field.\n";
				continue;
			}
			printInsertionSortReport(*selected, sortBy, recordDatasetDisplayName(ds));
		} else if (choice == 3) {
			runBinarySearchDemoWithIO(*selected, recordDatasetDisplayName(ds));
		} else if (choice == 4) {
			cout << "\nFirst 10 records - " << recordDatasetDisplayName(ds) << "\n";
			displayArrayPreview(*selected, 10);
		} else {
			cout << "Invalid option.\n";
		}

		waitToReturn();
	}
}

static void resultMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	while (true) {
		printSubtitle("Experiment Results");
		int nav;
		cout << "  1. Sorting (timing only)\n"
			<< "  2. Searching (timing only)\n"
			<< "  0. Return\n"
			<< "Enter choice: ";
		cin >> nav;
		switch (nav) {
		case 1:
			sortingMenu(false, cityA, cityB, cityC, combined);
			break;
		case 2:
			searchingMenu(false, cityA, cityB, cityC, combined);
			break;
		case 0:
			return;
		default:
			cout << "Invalid choice.\n";
		}
	}
}

void MainMenu(RecordArray& cityA, RecordArray& cityB, RecordArray& cityC, RecordArray& combined) {
	int nav;
	while (true) {
		printTitle("Main Menu");
		cout << "  1. Age group summary (all cities)\n"
			<< "  2. Carbon emission menu\n"
			<< "  3. Sorting experiment\n"
			<< "  4. Searching experiment\n"
			<< "  5. Experiment results (quiet)\n"
			<< "  6. Sorted array tools (memory / sort / binary demo)\n"
			<< "  0. Exit\n"
			<< "Enter choice: ";
		cin >> nav;

		switch (nav) {
		case 1:
			printAgeGroupHistogram(cityA, "City A - Metropolitan");
			printAgeGroupHistogram(cityB, "City B - University Town");
			printAgeGroupHistogram(cityC, "City C - Suburban/Rural");
			waitToReturn();
			break;
		case 2:
			emissionMenu();
			break;
		case 3:
			sortingMenu(true, cityA, cityB, cityC, combined);
			waitToReturn();
			break;
		case 4:
			searchingMenu(true, cityA, cityB, cityC, combined);
			waitToReturn();
			break;
		case 5:
			resultMenu(cityA, cityB, cityC, combined);
			break;
		case 6:
			sortedArrayToolsMenu(cityA, cityB, cityC, combined);
			break;
		case 0:
			cout << "Goodbye.\n";
			return;
		default:
			cout << "Invalid choice.\n";
		}
	}
}
