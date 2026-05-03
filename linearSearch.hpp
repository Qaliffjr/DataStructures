#pragma once
#include <string>
#include "ResidentArray.hpp"
#include "ResidentLinkedList.hpp"

// Array Functions:
void linearSearchArrayByAgeGroup(const ResidentArray& arr, const std::string& targetID);



// Linked List Functions:
ResidentLinkedList linearSearchListByAge(
    const ResidentLinkedList& list,
    int minAge,
    int maxAge
);

ResidentLinkedList linearSearchListByTransport(
    const ResidentLinkedList& list,
    const std::string& modeOfTransport
);

ResidentLinkedList linearSearchListByDailyDistance(
    const ResidentLinkedList& list,
    int minDistance,
    int maxDistance
);
