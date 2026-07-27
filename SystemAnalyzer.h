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
    vector<double> parseVector(const string& str) {
        vector<double> result;
        stringstream ss(str);
        double val;
        while (ss >> val) {
            result.push_back(val);
        }
        return result;
    }

public:
    SystemAnalyzer(const string& numaratorStr, const string& numitorStr) {
        numarator = parseVector(numaratorStr);
        numitor = parseVector(numitorStr);
    }

    void ErrorMsg() {
        if (numarator.empty() || numitor.empty()) {
            cout << "{\"error\": \"Vectori invalizi\"}";
            return;
        }

        string stabilitate = "Necunoscut";
        string poliStr = "-";
        string zerouriStr = "-";

        // calcul poli grad 2
        if (numitor.size() == 3) {
            double a = numitor[0], b = numitor[1], c = numitor[2];
            complex<double> delta = b * b - 4.0 * a * c;
            
            complex<double> p1 = (-b + sqrt(delta)) / (2.0 * a);
            complex<double> p2 = (-b - sqrt(delta)) / (2.0 * a);

            // verificare stabilitate
            if (p1.real() < 0 || p2.real() < 0) {
                stabilitate = "Sistem instabil";
            } 
            else {
                stabilitate = "Sistem stabil";
            }

            // formatare ca string
            stringstream ss;
            ss << p1.real() << (p1.imag() >= 0 ? "+" : "") << p1.imag() << "j, "
               << p2.real() << (p2.imag() >= 0 ? "+" : "") << p2.imag() << "j";
            poliStr = ss.str();
        } 
        // calcul poli grad 1
        else if (numitor.size() == 2) {
            double a = numitor[0], b = numitor[1];
            double p1 = -b / a;

            if (p1 < 0) {
                stabilitate = "Sistem instabil";
            } 
            else {
                stabilitate = "Sistem stabil";
            }

            stringstream ss;
            ss << p1;
            poliStr = ss.str();
        }

        //calcul zerouri gradul 1(grad maxim)
        if (numarator.size() == 2) {
            double z1 = -numarator[1] / numarator[0];
            stringstream ss;
            ss << z1;
            zerouriStr = ss.str();
        }

       
        cout << "{";
        cout << "\"stabilitate\":\"" << stabilitate << "\",";
        cout << "\"poli\":\"" << poliStr << "\",";
        cout << "\"zerouri\":\"" << zerouriStr << "\"";
        cout << "}";
    }
};