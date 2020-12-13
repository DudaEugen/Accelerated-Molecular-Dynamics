#include "utility/functions_for_derivative.hpp"
#include <stdexcept>

Const::Const(const double v) noexcept
    : value{ v }
{
}

double Const::compute_value(const double x) const noexcept { return value; }

double Const::compute_derivative(const double x) const noexcept { return 0; }

Const Const::set_parameters(const std::vector<double>& params) const
{
    return *this;
}

Parameter::Parameter(const uint8_t index) noexcept
    : index{ index }
{
}

double Parameter::compute_value(const double x) const 
{ 
    throw std::runtime_error("class Parameter don't have method compute_value"); 
}

double Parameter::compute_derivative(const double x) const noexcept { return 0; }

Const Parameter::set_parameters(const std::vector<double>& params) const
{
    return Const(params[index]);
}

double Variable::compute_value(const double x) const noexcept { return x; }

double Variable::compute_derivative(const double x) const noexcept { return 1; }

Variable Variable::set_parameters(const std::vector<double>& params) const
{
    return *this;
}
