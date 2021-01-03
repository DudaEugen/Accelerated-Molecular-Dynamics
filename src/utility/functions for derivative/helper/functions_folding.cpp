#include "utility/functions for derivative/helper/functions_folding.hpp"

double ZeroConstanta::operator() (double argument) const noexcept 
{ 
    return 0; 
}

ZeroConstanta ZeroConstanta::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}
