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

impl::Product_t<impl::Constanta, fcd::Parameter> fcd::operator- (Parameter p) noexcept
{
    return impl::product(impl::Constanta(-1), p);
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

impl::Summ_t<fcd::Parameter, fcd::Parameter> fcd::operator+ (Parameter p1, Parameter p2) noexcept
{
    return impl::summ(p1, p2);
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator+ (Variable v1, Variable v2) noexcept
{
    return impl::product(impl::Constanta(2), Variable());
}

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Summ_t<impl::Constanta, fcd::Parameter> fcd::operator+ (impl::Constanta c, Parameter p) noexcept
{
    return impl::summ(c, p);
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator+ (impl::Constanta c, Variable v) noexcept
{
    return impl::summ(c, v);
}

impl::Constanta fcd::operator+ (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return c2;
}

fcd::Parameter fcd::operator+ (impl::ZeroConstanta c, Parameter p) noexcept
{
    return p;
}

fcd::Variable fcd::operator+ (impl::ZeroConstanta c, Variable v) noexcept
{
    return v;
}

impl::Summ_t<impl::Constanta, fcd::Parameter> fcd::operator+ (Parameter p, impl::Constanta c) noexcept
{
    return impl::summ(c, p);
}

fcd::Parameter fcd::operator+ (Parameter p, impl::ZeroConstanta c) noexcept
{
    return p;
}

impl::Summ_t<fcd::Parameter, fcd::Variable> fcd::operator+ (Parameter p, Variable v) noexcept
{
    return impl::summ(p, v);
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator+ (Variable v, impl::Constanta c) noexcept
{
    return impl::summ(c, v);
}

fcd::Variable fcd::operator+ (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Summ_t<fcd::Parameter, fcd::Variable> fcd::operator+ (Variable v, Parameter p) noexcept
{
    return impl::summ(p, v);
}

impl::Constanta fcd::operator* (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0)*c2(0));
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<fcd::Parameter, fcd::Parameter> fcd::operator* (Parameter p1, Parameter p2) noexcept
{
    return impl::product(p1, p2);
}

impl::Function<impl::function_name::POWER, 
    fcd::Variable, impl::UnusedArgument, 2> fcd::operator* (Variable v1, Variable v2) noexcept
{
    return power<2>(Variable());
}

impl::ZeroConstanta fcd::operator* (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Parameter> fcd::operator* (impl::Constanta c, Parameter p) noexcept
{
    return impl::product(c, p);
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator* (impl::Constanta c, Variable v) noexcept
{
    return impl::product(c, v);
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c, Parameter p) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Parameter> fcd::operator* (Parameter p, impl::Constanta c) noexcept
{
    return impl::product(c, p);
}

impl::ZeroConstanta fcd::operator* (Parameter p, impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<fcd::Parameter, fcd::Variable> fcd::operator* (Parameter p, Variable v) noexcept
{
    return impl::product(p, v);
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator* (Variable v, impl::Constanta c) noexcept
{
    return impl::product(c, v);
}

impl::ZeroConstanta fcd::operator* (Variable v, impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<fcd::Parameter, fcd::Variable> fcd::operator* (Variable v, Parameter p) noexcept
{
    return impl::product(p, v);
}

impl::Constanta fcd::operator- (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::ZeroConstanta fcd::operator- (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Difference_t<fcd::Parameter, fcd::Parameter> fcd::operator- (Parameter p1, Parameter p2) noexcept
{
    return p1 + (-p2);
}

impl::ZeroConstanta fcd::operator- (Variable v1, Variable v2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Constanta fcd::operator- (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Difference_t<impl::Constanta, fcd::Parameter> fcd::operator- (impl::Constanta c, Parameter p) noexcept
{
    return c + (-p);
}

impl::Difference_t<impl::Constanta, fcd::Variable> fcd::operator- (impl::Constanta c, Variable v) noexcept
{
    return c + (-v);
}

impl::Constanta fcd::operator- (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::Product_t<impl::Constanta, fcd::Parameter> fcd::operator- (impl::ZeroConstanta c, Parameter p) noexcept
{
    return -p;
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator- (impl::ZeroConstanta c, Variable v) noexcept
{
    return -v;
}

impl::Summ_t<impl::Constanta, fcd::Parameter> fcd::operator- (Parameter p, impl::Constanta c) noexcept
{
    return p + impl::Constanta(-c(0));
}

fcd::Parameter fcd::operator- (Parameter p, impl::ZeroConstanta c) noexcept
{
    return p;
}

impl::Difference_t<fcd::Parameter, fcd::Variable> fcd::operator- (Parameter p, Variable v) noexcept
{
    return p + (-v);
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator- (Variable v, impl::Constanta c) noexcept
{
    return v + (-c);
}

fcd::Variable fcd::operator- (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Difference_t<fcd::Variable, fcd::Parameter> fcd::operator- (Variable v, Parameter p) noexcept
{
    return v + (-p);
}

impl::Constanta fcd::operator/ (impl::Constanta c1, impl::Constanta c2)
{
    return impl::Constanta(c1(0)/c2(0));
}

impl::Ratio_t<fcd::Parameter, fcd::Parameter> fcd::operator/ (Parameter p1, Parameter p2) noexcept
{
    return p1 * power<-1>(p2);
}

impl::Constanta fcd::operator/ (Variable v1, Variable v2) noexcept
{
    return impl::Constanta(1);
}

impl::Ratio_t<impl::Constanta, fcd::Parameter> fcd::operator/ (impl::Constanta c, fcd::Parameter p) noexcept
{
    return c * power<-1>(p);
}

impl::Ratio_t<impl::Constanta, fcd::Variable> fcd::operator/ (impl::Constanta c, Variable v) noexcept
{
    return c * power<-1>(v);
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c, Parameter p) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Parameter> fcd::operator/ (Parameter p, impl::Constanta c)
{
    return impl::Constanta(1/c(0)) * p;
}

impl::Ratio_t<fcd::Parameter, fcd::Variable> fcd::operator/ (Parameter p, Variable v) noexcept
{
    return p * power<-1>(v);
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator/ (Variable v, impl::Constanta c)
{
    return impl::Constanta(1/c(0)) * v;
}

impl::Ratio_t<fcd::Variable, fcd::Parameter> fcd::operator/ (Variable v, Parameter p) noexcept
{
    return v * power<-1>(p);
}
