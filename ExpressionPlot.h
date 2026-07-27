#pragma once

#include <vector>
#include <string>
#include "ExpressionPoint.h"

class ExpressionPlot
{
private:
    double step;
    double duration;
    std::string expression;

public:
    ExpressionPlot(
        double step,
        double duration,
        const std::string& expression
    );

    std::vector<ExpressionPoint> Generate();
};