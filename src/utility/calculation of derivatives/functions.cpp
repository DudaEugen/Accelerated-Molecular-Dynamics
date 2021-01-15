#include "calculation of derivatives/functions.hpp"

namespace fcd = utils::fcd;
namespace impl = utils::fcd::implementation;

impl::Constanta fcd::operator- (impl::Constanta c) noexcept
{
    return impl::Constanta(-c(0));
}

impl::ZeroConstanta fcd::operator- (impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}
    
impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator- (Variable v) noexcept
{
    return impl::product(impl::Constanta(-1), v);
}

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) + c2(0));
}

impl::ZeroConstanta fcd::operator+ (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator+ (Variable v1, Variable v2) noexcept
{
    return impl::product(impl::Constanta(2), Variable());
}

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator+ (impl::Constanta c, Variable v) noexcept
{
    return impl::summ(c, v);
}

impl::Constanta fcd::operator+ (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return c2;
}

fcd::Variable fcd::operator+ (impl::ZeroConstanta c, Variable v) noexcept
{
    return v;
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator+ (Variable v, impl::Constanta c) noexcept
{
    return impl::summ(c, v);
}

fcd::Variable fcd::operator+ (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Constanta fcd::operator* (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0)*c2(0));
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Function<impl::FunctionName::Power, 
    fcd::Variable, impl::UnusedArgument, 2> fcd::operator* (Variable v1, Variable v2) noexcept
{
    return power<2>(Variable());
}

impl::ZeroConstanta fcd::operator* (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator* (impl::Constanta c, Variable v) noexcept
{
    return impl::product(c, v);
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator* (Variable v, impl::Constanta c) noexcept
{
    return impl::product(c, v);
}

impl::ZeroConstanta fcd::operator* (Variable v, impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}

impl::Constanta fcd::operator- (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::ZeroConstanta fcd::operator- (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator- (Variable v1, Variable v2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Constanta fcd::operator- (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Difference_t<impl::Constanta, fcd::Variable> fcd::operator- (impl::Constanta c, Variable v) noexcept
{
    return c + (-v);
}

impl::Constanta fcd::operator- (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator- (impl::ZeroConstanta c, Variable v) noexcept
{
    return -v;
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator- (Variable v, impl::Constanta c) noexcept
{
    return v + (-c);
}

fcd::Variable fcd::operator- (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Constanta fcd::operator/ (impl::Constanta c1, impl::Constanta c2)
{
    return impl::Constanta(c1(0)/c2(0));
}

impl::Constanta fcd::operator/ (Variable v1, Variable v2) noexcept
{
    return impl::Constanta(1);
}


impl::Ratio_t<impl::Constanta, fcd::Variable> fcd::operator/ (impl::Constanta c, Variable v) noexcept
{
    return c * power<-1>(v);
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator/ (Variable v, impl::Constanta c)
{
    return impl::Constanta(1/c(0)) * v;
}
