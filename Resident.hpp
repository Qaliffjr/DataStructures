#pragma once //use pragma to ensure that the file is only included once

struct Resident {
    char residentID[16];
    int age;
    char transportMode[32];
    double dailyDistance;
    double emissionFactor;
    int averageDaysPerMonth;
};  