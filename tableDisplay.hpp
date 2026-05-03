#pragma once
#include <string>

void printSeparator(int totalWidth, char fillChar = '=');

void printRow(const std::string data[], const int widths[], int cols);

void printTable(
    const std::string headers[],
    int headerCount,
    const std::string rows[][10],   // max 10 columns
    int rowCount,
    const int widths[]
);