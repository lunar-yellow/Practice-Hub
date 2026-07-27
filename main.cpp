#include <iostream>
#include <string>

#include "ExpressionPlot.h"
#include "SystemAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {

    // face anaiza sistemului
    // argc == 3 --> [0]program.exe, [1]numarator, [2]numitor --cate argumente luam pentru analiza functiei de transfer
    if (argc == 3) {
        string numarator = argv[1];
        string numitor = argv[2];

        SystemAnalyzer analyzer(numarator, numitor);
        analyzer.ErrorMsg(); // Afiseaza direct JSON-ul
    } 

    //  generam punctele pentru grafic
    // argc == 4 --> [0]program.exe, [1]step, [2]duration, [3]expression --cate argumente luam pentru grafic
    else if (argc == 4) {
        double step = stod(argv[1]);
        double duration = stod(argv[2]); 
        string expression = argv[3];

        ExpressionPlot plot(step, duration, expression);
        auto points = plot.Generate();

        // constructia vectorului [time,value]
        cout << "[";
        for (size_t i = 0; i < points.size(); i++) {
            cout << "{\"time\":" << points[i].time << ",\"value\":" << points[i].value << "}";
            if (i != points.size() - 1) {
                cout << ",";
            }
        }
        cout << "]";
    }

    return 0;
}