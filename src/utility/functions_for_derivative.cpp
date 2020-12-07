#include "utility/functions_for_derivative.hpp"

Const::Const(double v)
    : value{ v }
{
}

double Const::get_value(double x) { return value; }

double Const::compute_derivative(double x) { return 0; }

double Variable::get_value(double x) { return x; }

double Variable::compute_derivative(double x) { return 1; }
