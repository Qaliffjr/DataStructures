#include <iostream>
#include "CSVLoader.hpp"

using namespace std;

//Data Initialization

void initData() {
    string file1 = "dataset1-cityA.csv";
    string file2 = "dataset2-cityB.csv";
    string file3 = "dataset3-cityC.csv";

    // Adjusting Array Containers

    int size1 = countLines(file1);
    RecordArray arr1;
    arr1.arr = new Record[size1];
    arr1.size = 0;
    arr1.capacity = size1;

    int size2 = countLines(file2);
    RecordArray arr2;
    arr2.arr = new Record[size2];
    arr2.size = 0;
    arr2.capacity = size2;

    int size3 = countLines(file3);
    RecordArray arr3;
    arr3.arr = new Record[size3];
    arr3.size = 0;
    arr3.capacity = size3;


    // Record Names for Linked Lists
    RecordLinkedList list1;
    list1.head = nullptr;
    list1.tail = nullptr;

    RecordLinkedList list2;
    list2.head = nullptr;
    list2.tail = nullptr;

    RecordLinkedList list3;
    list3.head = nullptr;
    list3.tail = nullptr;


    // Actual Loading of CSV files into the respective data structures
    loadCSV(file1, arr1, list1);
    loadCSV(file2, arr2, list2);
    loadCSV(file3, arr3, list3);
}


int main() {
    //Initialize Data
    initData();

    //Program Navigation


    return 0;
}