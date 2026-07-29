#include <iostream>
#include <string>
#include <algorithm> // pentru std::for_each

#include "ExpressionPlot.h"
#include "SystemAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {

    // verificare numar minim de argumente
    if (argc < 2) {
        cout << "{\"error\": \"Numar insuficient de argumente!\"}";
        return 1;
    }

    // face analiza sistemului
    // argc == 3 --> [0]program.exe, [1]numarator, [2]numitor
    if (argc == 3) {
        string numarator = argv[1];
        string numitor = argv[2];

        SystemAnalyzer analyzer(numarator, numitor);
        analyzer.ErrorMsg(); // afiseaza direct JSON-ul
    } 

    // generam punctele pentru grafic
    // argc == 4 --> [0]program.exe, [1]step, [2]duration, [3]expression
    else if (argc == 4) {
        double step = stod(argv[1]);
        double duration = stod(argv[2]); 
        string expression = argv[3];

        ExpressionPlot plot(step, duration, expression);
        auto points = plot.Generate();

        if (points.empty()) 
        {
        std::cout << "{\"error\": \"Pas invalid(maxim 10^(-5)) sau expresie matematica incorecta!\"}";
        return 0; //pentru afisare si oprire 
        }


        // constructia vectorului [time,value]
        cout << "[";
        
        std::for_each(points.begin(), points.end(), [&](const auto& point) {
            cout << "{\"time\":" << point.time << ",\"value\":" << point.value << "}";
            
            //verificam daca elementul curent la care e nu este ultimul din vector
            if (&point != &points.back()) {
                cout << ",";
            }
        });

        cout << "]";
    }

    return 0;
}