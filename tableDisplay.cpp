#include "TableDisplay.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


void printSeparator(int totalWidth, char fillChar) {
    cout << setfill(fillChar) << setw(totalWidth) << "" << setfill(' ') << "\n";
}

void printRow(const string data[], const int widths[], int cols) {
    for (int i = 0; i < cols; i++) {
        cout << left << setw(widths[i]) << data[i];
    }
    cout << "\n";
}

void printTable(
    const string headers[],
    int headerCount,
    const string rows[][10],
    int rowCount,
    const int widths[]
) {
    int totalWidth = 0;

    for (int i = 0; i < headerCount; i++) {
        totalWidth += widths[i];
    }

    // Header
    printSeparator(totalWidth);
    printRow(headers, widths, headerCount);
    printSeparator(totalWidth, '-');

    // Rows
    for (int i = 0; i < rowCount; i++) {
        printRow(rows[i], widths, headerCount);
    }

    printSeparator(totalWidth);
}