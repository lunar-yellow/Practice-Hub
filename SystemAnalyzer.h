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

    // Transforma string-ul primit (ex "1 0 3") intr-un vector de numere
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

        // 1. Calcul Poli - Gradul 2 (ex: 1 0 3 -> a=1, b=0, c=3)
        if (numitor.size() == 3) {
            double a = numitor[0], b = numitor[1], c = numitor[2];
            complex<double> delta = b * b - 4.0 * a * c;
            
            complex<double> p1 = (-b + sqrt(delta)) / (2.0 * a);
            complex<double> p2 = (-b - sqrt(delta)) / (2.0 * a);

            // Verificare simpla: doar Stabil sau Instabil
            if (p1.real() < 0 || p2.real() < 0) {
                stabilitate = "Sistem instabil";
            } 
            else {
                stabilitate = "Sistem stabil";
            }

            // Formatam polii ca string
            stringstream ss;
            ss << p1.real() << (p1.imag() >= 0 ? "+" : "") << p1.imag() << "j, "
               << p2.real() << (p2.imag() >= 0 ? "+" : "") << p2.imag() << "j";
            poliStr = ss.str();
        } 
        // 2. Calcul Poli - Gradul 1 (ex: 1 2 -> a=1, b=2)
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

        // 3. Calcul Zerouri (pentru numarator de gradul 1)
        if (numarator.size() == 2) {
            double z1 = -numarator[1] / numarator[0];
            stringstream ss;
            ss << z1;
            zerouriStr = ss.str();
        }

        // 4. Afisare JSON
        cout << "{";
        cout << "\"stabilitate\":\"" << stabilitate << "\",";
        cout << "\"poli\":\"" << poliStr << "\",";
        cout << "\"zerouri\":\"" << zerouriStr << "\"";
        cout << "}";
    }
};