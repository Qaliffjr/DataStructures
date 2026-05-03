#include "LinkedList.hpp"
#include "SearchSortedList.hpp"
#include "ResidentLinkedList.hpp"

#include <iostream>
using namespace std;


// ============================================================
//  Filter selection (replace to main later)
// ============================================================
void runSearch(Node* head) {
    //search criteria selection
    int searchChoice;
    cout << "Search by: (1) Age  (2) Distance  (3) Transport: ";
    cin >> searchChoice;

    if (searchChoice == 1) {
        //prepare sorted list(age)
        sortList(head, 1);

        // age group selection
        cout << "Age Group:" << endl;
        cout << "1. Children & Teenagers (6-17)" << endl;
        cout << "2. Young Adults (18-25)" << endl;
        cout << "3. Working Adults Early (26-45)" << endl;
        cout << "4. Working Adults Late (46-60)" << endl;
        cout << "5. Senior Citizens (61-100)" << endl;
        
        int group;
        cin >> group;
        
        if (group == 1) {
            searchByAge(head, 6, 17);
        }
        else if (group == 2) {
            searchByAge(head, 18, 25);
        }
        else if (group == 3) {
            searchByAge(head, 26, 45);
        }
        else if (group == 4) {
            searchByAge(head, 46, 60);
        }
        else if (group == 5) {
            searchByAge(head, 61, 100);
        }

    }
    else if (searchChoice == 2) {
		//prepare sorted list(distance)
        sortList(head, 2);

        //range selection
        cout << "Distance:" << endl;
        cout << "1. Short (< 5km)" << endl;
        cout << "2. Medium (6-15km)" << endl;
        cout << "3. Long (> 15km)" << endl;

        int dist;
        cin >> dist;

        if (dist == 1) {
            searchByDistance(head, 0, 5);
		}
        else if (dist == 2) {
            searchByDistance(head, 6, 15);
		}
        else if (dist == 3) {
            searchByDistance(head, 16, 100);
        }

    }
    else if (searchChoice == 3) {
        //mode selection
        cout << "Transport Mode:" << endl;
        cout << "1. Bicycle" << endl;
        cout << "2. Walking" << endl;
        cout << "3. School Bus" << endl;
        cout << "4. Carpool" << endl;
        cout << "5. Bus" << endl;
        cout << "6. Car" << endl;

        int mode;
        cin >> mode;

        if (mode == 1) {
            searchByTransport(head, "Bicycle");
		}
        else if (mode == 2) {
            searchByTransport(head, "Walking");
		}
        else if (mode == 3) {
            searchByTransport(head, "School Bus");
		}
        else if (mode == 4) {
            searchByTransport(head, "Carpool");
		}
        else if (mode == 5) {
            searchByTransport(head, "Bus");
		}
        else if (mode == 6) {
            searchByTransport(head, "Car");
        }
    }
}


//find start node
Node* findStartNode(Node* head, double minValue, int sortBy) {
    int length = 0;
    Node* current = head;

    while (current != nullptr) {
        length++;
        current = current->next;
    }

    int left = 0;
    int right = length - 1;
    Node* result = nullptr;

    while (left <= right) {
        //mid index
        int mid = (left + right) / 2;
        //start - mid
        Node* midNode = head;
        for (int i = 0; i < mid; i++) {
            midNode = midNode->next;
        }
        // sortBy what?
        double midValue;
        if (sortBy == 1)      midValue = midNode->data.Age;
        else if (sortBy == 2) midValue = midNode->data.dailyDistance;

        //right
        if (midValue >= minValue) {
            result = midNode;
            right = mid - 1;
        }
        //left
        else {
            left = mid + 1;
        }
    }
    return result;
}


// ============================================================
// Search by Age Group
// ============================================================
//6-17, 18-25, 26-45, 46-60, 61-100
void searchByAge(Node* head, int minAge, int maxAge) {
	Node* startNode = findStartNode(head, minAge, 1);

    if (startNode == nullptr) {
        cout << "No data fund" << endl;
        return;
    }

    cout << "--- Age Group: " << minAge << " - " << maxAge << " ---" << endl;

    int count = 0;

    Node* current = startNode;

    //Output
    while (current != nullptr && current->data.Age <= maxAge) {
        cout << "ID: " << current->data.ID << endl;
        cout << "Age: " << current->data.Age << endl;
        cout << "Transport: " << current->data.modeOfTransport << endl;
        cout << "Distance: " << current->data.dailyDistance << endl;
        cout << "Carbon: " << current->data.carbonEmissionFactor << endl;
        cout << "----------------------------" << endl;
        count++;
        current = current->next;
    }
	//total
    cout << "Total records found: " << count << endl;
}


// ============================================================
//  Search by Distance
// ============================================================
//< 5 KM,6 - 15 KM,> 15 KM
void searchByDistance(Node* head, int minDist, int maxDist) {
    Node* startNode = findStartNode(head, minDist, 2);

    if (startNode == nullptr) {
        cout << "No data found" << endl;
        return;
    }

    //output
    cout << "--- Distance " << minDist << "km - " << maxDist << "km ---" << endl;
    int count = 0;
    Node* current = startNode;
    while (current != nullptr && current->data.dailyDistance <= maxDist) {
        cout << "ID: " << current->data.ID << endl;
        cout << "Age: " << current->data.Age << endl;
        cout << "Transport: " << current->data.modeOfTransport << endl;
        cout << "Distance: " << current->data.dailyDistance << endl;
        cout << "Carbon: " << current->data.carbonEmissionFactor << endl;
        cout << "----------------------------" << endl;
        count++;
        current = current->next;
    }
    //total
    cout << "Total: " << count << " records" << endl;
}


// ============================================================
// Search by Transport Mode
// ============================================================
//bicycle, walking, school bus, carpool, bus, car
void searchByTransport(Node* head, const string& mode) {
    sortList(head, 4);

    cout << "--- Transport: " << mode << " ---" << endl;
    
    int count = 0;
    Node* current = head;
    
    while (current != nullptr) {
        if (current->data.modeOfTransport == mode) {
            cout << "ID: " << current->data.ID << endl;
            cout << "Age: " << current->data.Age << endl;
            cout << "Transport: " << current->data.modeOfTransport << endl;
            cout << "Distance: " << current->data.dailyDistance << endl;
            cout << "Carbon: " << current->data.carbonEmissionFactor << endl;
            cout << "----------------------------" << endl;
            count++;
        }
        current = current->next;
    }
    cout << "Total: " << count << " records" << endl;
}
