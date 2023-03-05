#include "CancerData.h"

CancerData::CancerData(const string& country, double cancerRate) : countryName(country), cancerRate(cancerRate) {}

CancerData::CancerData(const CancerData& other) : countryName(other.countryName), cancerRate(other.cancerRate) {}

CancerData& CancerData::operator=(const CancerData& other) {
    if (this != &other) {
        countryName = other.countryName;
        cancerRate = other.cancerRate;
    }
    return *this;
}

CancerData::CancerData(CancerData&& other) noexcept : countryName(move(other.countryName)), cancerRate(other.cancerRate) {}

CancerData& CancerData::operator=(CancerData&& other) noexcept {
    if (this != &other) {
        countryName = move(other.countryName);
        cancerRate = other.cancerRate;
    }
    return *this;
}

CancerData::~CancerData() {}

string CancerData::getCountry() const {
    return countryName;
}

double CancerData::getRate() const {
    return cancerRate;
}

void CancerData::setCountry(string country) {
    countryName = countryName;
}

void CancerData::setRate(double rate) {
    cancerRate = rate;
}

