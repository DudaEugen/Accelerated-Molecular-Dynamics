#include "calculation of derivatives/helper/functions_folding.hpp"

namespace impl = utils::fcd::implementation;

double impl::ZeroConstanta::operator() (double argument) const noexcept 
{ 
    return 0; 
}

impl::ZeroConstanta impl::ZeroConstanta::set_parameters(const std::vector<double>& params) const noexcept
{
    return *this;
}
