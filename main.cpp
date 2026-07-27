#include <iostream>
#include <string>

#include "ExpressionPlot.h"
#include "SystemAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {

    // 1. Daca primim 2 parametri din Python -> Facem Analiza Sistemului
    // argc == 3 inseamna: [0]program.exe, [1]numarator, [2]numitor
    if (argc == 3) {
        string numarator = argv[1];
        string numitor = argv[2];

        SystemAnalyzer analyzer(numarator, numitor);
        analyzer.ErrorMsg(); // Afiseaza direct JSON-ul
    } 

    // 2. Daca primim 3 parametri din Python -> Generam Punctele pentru Grafic
    // argc == 4 inseamna: [0]program.exe, [1]step, [2]duration, [3]expression
    else if (argc == 4) {
        double step = stod(argv[1]);
        double duration = stod(argv[2]);
        string expression = argv[3];

        ExpressionPlot plot(step, duration, expression);
        auto points = plot.Generate();

        // Constructie simpla de JSON vector: [{"time":0, "value":1}, ...]
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