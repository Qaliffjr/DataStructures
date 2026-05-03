#pragma once
#include <string>
#include "Resident.hpp"

struct Node {
    Resident data;
    Node* next;
};

struct ResidentLinkedList {
    Node* head;
    Node* tail;
};
