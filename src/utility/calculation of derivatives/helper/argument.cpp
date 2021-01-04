#include "calculation of derivatives/helper/argument.hpp"
#include <stdexcept>
#include <cmath>

utils::fcd::Constanta::Constanta(double value) noexcept 
    : value{ value }
{
}

double utils::fcd::Constanta::operator() (double argument) const noexcept 
{ 
    return value; 
}

utils::fcd::Constanta utils::fcd::Constanta::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}

utils::fcd::Parameter::Parameter(std::uint8_t i) noexcept 
    : index{ i }
{
}

double utils::fcd::Parameter::operator() (double argument) const
{
    throw std::runtime_error("Parameter in function for derivative don't initializing!");
}

utils::fcd::Constanta utils::fcd::Parameter::set_parameters(const std::vector<double>& params) const
{
    return Constanta(params[index]);
}

double utils::fcd::Variable::operator() (double argument) const noexcept 
{ 
    return argument; 
}

utils::fcd::Variable utils::fcd::Variable::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}
