#include "calculation of derivatives/helper/argument.hpp"
#include <stdexcept>
#include <cmath>

utils::fcd::implementation::Constanta::Constanta(double value) noexcept 
    : value{ value }
{
}

utils::fcd::implementation::Constanta::Constanta(int value) noexcept 
    : value{ static_cast<double>(value) }
{
}

double utils::fcd::implementation::Constanta::operator() (double argument, 
                                    const std::vector<double>* dynamicParameters) const noexcept 
{ 
    return value; 
}

double utils::fcd::implementation::Constanta::operator() (double argument, double dynamicParameterValue) const noexcept 
{ 
    return value; 
}

double utils::fcd::Variable::operator() (double argument, const std::vector<double>* dynamicParameters) const noexcept 
{ 
    return argument; 
}

double utils::fcd::Variable::operator() (double argument, double dynamicParameterValue) const noexcept 
{ 
    return argument; 
}

double utils::fcd::implementation::ZeroConstanta::operator() (double argument, 
                                    const std::vector<double>* dynamicParameters) const noexcept 
{ 
    return 0; 
}

double utils::fcd::implementation::ZeroConstanta::operator() (double argument, double dynamicParameter) const noexcept 
{ 
    return 0; 
}

double utils::fcd::DynamicParameter::operator() (double argument, double dynamicParameterValue) const noexcept
{
    return dynamicParameterValue;
}
