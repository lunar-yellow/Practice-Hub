
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>

#include "SystemAnalyzer.h"

using namespace std;

// transformare string primit ex: "1 2 2" in vector
vector<double> SystemAnalyzer::parseVector(const string& str) {
    vector<double> result;
    stringstream ss(str);
    double val;
    while (ss >> val) { 
        result.push_back(val);
    }
    return result;
}

SystemAnalyzer::SystemAnalyzer(const string& numaratorStr, const string& numitorStr) {
    numarator = parseVector(numaratorStr);
    numitor = parseVector(numitorStr);
}

void SystemAnalyzer::ErrorMsg() {
    if (numarator.empty() || numitor.empty()) {
        cout << "{\"error\": \"Vectori invalizi\"}";
        return;
    }

    string stabilitate = "Necunoscut";
    string poliStr = "-";
    string zerouriStr = "-";

    // calcul poli de gradul 2
    if (numitor.size() == 3) {
        double a = numitor[0], b = numitor[1], c = numitor[2];
        complex<double> delta = b * b - 4.0 * a * c;
        
        complex<double> p1 = (-b + sqrt(delta)) / (2.0 * a);
        complex<double> p2 = (-b - sqrt(delta)) / (2.0 * a);

        // verificare stabilitate cu marja de eroare (1e-6)
        if (p1.real() > 1e-6 || p2.real() > 1e-6)   
        {
            stabilitate = "Sistem instabil";
        } 
        else
         if (abs(p1.real()) <= 1e-6 || abs(p2.real()) <= 1e-6) 
            {
                stabilitate = "Sistem la limita stabilitatii";
            } 
                else 
                {
                    stabilitate = "Sistem stabil";
                }

        // formatare poli ca string pentru afisare
        stringstream ss;
        ss << p1.real() << (p1.imag() >= 0 ? "+" : "") << p1.imag() << "j, "
           << p2.real() << (p2.imag() >= 0 ? "+" : "") << p2.imag() << "j";
        poliStr = ss.str();
    } 
    //  calcul poli de gradul 1
    else if (numitor.size() == 2) {
        double a = numitor[0], b = numitor[1];
        double p1 = -b / a;

        // verificare stabilitate cu marja de eroare (1e-6)
        if (p1 > 1e-6)  
        {
            stabilitate = "Sistem instabil";
        } 
        else 
            if (abs(p1) <= 1e-6) 
            {
                stabilitate = "Sistem la limita stabilitatii";
            } 
            else 
            {
                stabilitate = "Sistem stabil";
            }

        stringstream ss;
        ss << p1;
        poliStr = ss.str();
    }

    // calcul zerouri grad1
    if (numarator.size() == 2) {
        double z1 = -numarator[1] / numarator[0];
        stringstream ss;
        ss << z1;
        zerouriStr = ss.str();
    }

    //afisare rez json
    cout << "{";
    cout << "\"stabilitate\":\"" << stabilitate << "\",";
    cout << "\"poli\":\"" << poliStr << "\",";
    cout << "\"zerouri\":\"" << zerouriStr << "\"";
    cout << "}";
}