#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "CSVLoader.hpp" 
#include "recordLinkedList.hpp" 

void sortList(Node*& head, int sortBy);
void sortedInsert(Node*& sortedHead, Node* newNode, int sortBy);
bool isSmaller(Node* a, Node* b, int sortBy);

//check sorted list
void displayList(Node* head);

#endif