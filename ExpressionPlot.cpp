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

    // protectie impotriva unui crash al aplicatiei cand val pasului este ft mare si exista ft multe puncte de calculat
if (step <= 0 || step < 1e-5 || step > duration)
{
    return points; 
}
    te_parser convert;

    double t = 0;
//imi converteste expresia introdusa dintr un string intr o expresie valida cu ajutorul a tinyexpr.h
    convert.set_variables_and_functions({
        te_variable{"t", &t},
        te_variable{"pi", M_PI}
    });

    convert.compile(expression);

    if (!convert.success())
    {
        return points;
    }

    //nu putem implementa cu std::for_each in acest caz din cauza ca acesta lucreaza doar cu adrese ale unor 
    //elemente existente din memorie iar aici punctele inca nu au fost calculate
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