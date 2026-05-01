#include "CSVParser.hpp"
#include <cstring>
#include <fstream>

double computeMonthlyEmissions(double dailyDistance, double emissionFactor, int averageDaysPerMonth) {
    return dailyDistance * emissionFactor * static_cast<double>(averageDaysPerMonth);
}

static void stripTrailingCr(char* line) {
    const size_t len = std::strlen(line);
    if (len > 0 && line[len - 1] == '\r') {
        line[len - 1] = '\0';
    }
}

static void copyField(char* dest, size_t destSize, const char* src) {
    if (destSize == 0) return;
#if defined(_MSC_VER)
    strncpy_s(dest, destSize, src, _TRUNCATE);   // MSVC safe version, no std:: prefix
#else
    std::strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
#endif
}

static void safeCopy(char* dest, size_t destSize, const char* src) {
#if defined(_MSC_VER)
    strcpy_s(dest, destSize, src);               // MSVC safe version, no std:: prefix
#else
    std::strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
#endif
}

bool parseResidentCsvLine(const char* line, Resident& outResident) {
    if (line == nullptr || line[0] == '\0') return false;

    char buffer[512];
    if (std::strlen(line) >= sizeof(buffer)) return false;

    safeCopy(buffer, sizeof(buffer), line);      // replaces unsafe std::strcpy
    stripTrailingCr(buffer);

    char idBuf[16];
    char modeBuf[32];
    int age = 0;
    double dailyDistance = 0.0;
    double emissionFactor = 0.0;
    int averageDays = 0;

    int matched = 0;
#if defined(_MSC_VER)
    matched = sscanf_s(                          // no std:: prefix, MSVC-specific
        buffer,
        "%15[^,],%d,%31[^,],%lf,%lf,%d",
        idBuf, static_cast<unsigned>(sizeof(idBuf)),
        &age,
        modeBuf, static_cast<unsigned>(sizeof(modeBuf)),
        &dailyDistance,
        &emissionFactor,
        &averageDays);
#else
    matched = std::sscanf(
        buffer,
        "%15[^,],%d,%31[^,],%lf,%lf,%d",
        idBuf,
        &age,
        modeBuf,
        &dailyDistance,
        &emissionFactor,
        &averageDays);
#endif

    if (matched != 6) return false;

    outResident = Resident{};
    copyField(outResident.residentID, sizeof(outResident.residentID), idBuf);
    outResident.age = age;
    copyField(outResident.transportMode, sizeof(outResident.transportMode), modeBuf);
    outResident.dailyDistance = dailyDistance;
    outResident.emissionFactor = emissionFactor;
    outResident.averageDaysPerMonth = averageDays;
    outResident.monthlyEmissions = computeMonthlyEmissions(dailyDistance, emissionFactor, averageDays);
    return true;
}

bool loadCsvToArray(const char* filePath, ResidentArray& outArray) {
    if (filePath == nullptr || filePath[0] == '\0') return false;

    std::ifstream in(filePath);
    if (!in) return false;

    char header[1024];
    if (!in.getline(header, static_cast<std::streamsize>(sizeof(header)))) return false;

    char line[512];
    while (in.getline(line, static_cast<std::streamsize>(sizeof(line)))) {
        stripTrailingCr(line);
        if (line[0] == '\0') continue;

        Resident row{};
        if (!parseResidentCsvLine(line, row)) {
            in.close();
            return false;
        }
        if (!pushBack(outArray, row)) {
            in.close();
            return false;
        }
    }

    in.close();
    return true;
}