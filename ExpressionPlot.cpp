#define _USE_MATH_DEFINES

#include <cmath>
#include "ExpressionPlot.h"
#include "tinyexpr.h"

ExpressionPlot::ExpressionPlot(
    double step,
    double duration,
    const std::string& expression)
{
    this->step = step;
    this->duration = duration;
    this->expression = expression;
}

std::vector<ExpressionPoint> ExpressionPlot::Generate()
{
    std::vector<ExpressionPoint> points;

    te_parser convert;

    double t = 0;

    convert.set_variables_and_functions({
        te_variable{"t", &t},
        te_variable{"pi", M_PI}
    });

    convert.compile(expression);

    if (!convert.success())
    {
        return points;
    }

    for (t = 0; t <= duration; t += step)
    {
        double y = convert.evaluate();

        if (fabs(y) < 1e-6) // marja de eroare
            y = 0;

        points.push_back({
            t,
            y
        });
    }

    return points;
}