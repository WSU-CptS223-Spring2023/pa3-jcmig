#ifndef CANCERDATA_H
#define CANCERDATA_H

#include <string>
#include <stdio.h>
#include <iostream>

using std::string;
using std::max;
using std::cout;
using std::endl;
using std::move;

class CancerData {
public:
    // Primary Constructor
    explicit CancerData(const std::string& country = "", double rate = 0.0);

    // Copy Functions
    CancerData(const CancerData& other);
    CancerData& operator=(const CancerData& other);
    
    // Move Functions - noexcept used as it is assumed that no exceptions will be thrown to them
    CancerData(CancerData&& other) noexcept;
    CancerData& operator=(CancerData&& other) noexcept;

    // Destructor
    ~CancerData();

    // Getter Functions
    string getCountry() const;
    double getRate() const;

    // Setter Functions
    void setCountry(string country);
    void setRate(double rate);

private:
    string countryName;
    double cancerRate;
};

#endif CANCERDATA_H