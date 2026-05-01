#pragma once
#include <string>
#include "record.hpp"

struct Node {
    Record data;
    Node* next;
};

struct RecordLinkedList {
    Node* head;
    Node* tail;
};
