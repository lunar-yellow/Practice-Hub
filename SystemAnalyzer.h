#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <complex>
#include <cmath>

using namespace std;

class SystemAnalyzer {
private:
    vector<double> numarator;
    vector<double> numitor;

    // transformare string primit ex: 1 2 in vector
    vector<double> parseVector(const string& str);

public:
    SystemAnalyzer(const string& numaratorStr, const string& numitorStr);

    void ErrorMsg();
};