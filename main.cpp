#include <iostream> 
#include "CSVLoader.hpp" 
#include "menu.hpp" 
#include "DataStore.hpp"
#include "SortedArraySort.hpp"

using namespace std;

void initData() {
    string file1 = "dataset1-cityA.csv";
    string file2 = "dataset2-cityB.csv";
    string file3 = "dataset3-cityC.csv";

	//Allocate arrays based on line count of each file
    int size1 = countLines(file1);
    arr1.arr = new Resident[size1];
    arr1.size = 0;
    arr1.capacity = size1;

    int size2 = countLines(file2);
    arr2.arr = new Resident[size2];
    arr2.size = 0;
    arr2.capacity = size2;

    int size3 = countLines(file3);
    arr3.arr = new Resident[size3];
    arr3.size = 0;
    arr3.capacity = size3;

    //Initialize linked lists
    list1.head = list1.tail = nullptr;
    list2.head = list2.tail = nullptr;
    list3.head = list3.tail = nullptr;

    // Load CSV
    loadCSV(file1, arr1, list1);
    loadCSV(file2, arr2, list2);
    loadCSV(file3, arr3, list3);
}

int main() {
    initData();
    MainMenu();
    return 0;
}
