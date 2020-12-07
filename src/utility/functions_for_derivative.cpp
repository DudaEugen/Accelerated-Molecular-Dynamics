#include "utility/functions_for_derivative.hpp"

Const::Const(const double v) noexcept
    : value{ v }
{
}

double Const::get_value(const double x) const noexcept { return value; }

double Const::compute_derivative(const double x) const noexcept { return 0; }

double Variable::get_value(const double x) const noexcept { return x; }

double Variable::compute_derivative(const double x) const noexcept { return 1; }
