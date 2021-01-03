#include "utility/functions for derivative/helper/argument.hpp"
#include <stdexcept>
#include <cmath>

Constanta::Constanta(double value) noexcept 
    : value{ value }
{
}

double Constanta::operator() (double argument) const noexcept 
{ 
    return value; 
}

Constanta Constanta::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}

Parameter::Parameter(std::uint8_t i) noexcept 
    : index{ i }
{
}

double Parameter::operator() (double argument) const
{
    throw std::runtime_error("Parameter in function for derivative don't initializing!");
}

Constanta Parameter::set_parameters(const std::vector<double>& params) const
{
    return Constanta(params[index]);
}

double Variable::operator() (double argument) const noexcept 
{ 
    return argument; 
}

Variable Variable::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}
