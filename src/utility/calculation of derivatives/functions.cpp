#include "calculation of derivatives/functions.hpp"

namespace fcd = utils::fcd;
namespace impl = utils::fcd::implementation;

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) + c2(0));
}

impl::ZeroConstanta fcd::operator+ (impl::ZeroConstanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Function<impl::function_name::SUMM,
    fcd::Parameter, fcd::Parameter, impl::UnusedParameter> fcd::operator+ (Parameter p1, Parameter p2) noexcept
{
    return impl::summ(p1, p2);
}

impl::Function<impl::function_name::PRODUCT, 
    impl::Constanta, fcd::Variable, impl::UnusedParameter> fcd::operator+ (Variable v1, Variable v2) noexcept
{
    return impl::product(impl::Constanta(2), Variable());
}

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Function<impl::function_name::SUMM, 
    impl::Constanta, fcd::Parameter, impl::UnusedParameter> fcd::operator+ (impl::Constanta c, Parameter p) noexcept
{
    return impl::summ(c, p);
}

impl::Function<impl::function_name::SUMM, 
    impl::Constanta, fcd::Variable, impl::UnusedParameter> fcd::operator+ (impl::Constanta c, Variable v) noexcept
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

impl::Function<impl::function_name::SUMM, 
    impl::Constanta, fcd::Parameter, impl::UnusedParameter> fcd::operator+ (Parameter p, impl::Constanta c) noexcept
{
    return impl::summ(c, p);
}

fcd::Parameter fcd::operator+ (Parameter p, impl::ZeroConstanta c) noexcept
{
    return p;
}

impl::Function<impl::function_name::SUMM, 
    fcd::Parameter, fcd::Variable, impl::UnusedParameter> fcd::operator+ (Parameter p, Variable v) noexcept
{
    return impl::summ(p, v);
}

impl::Function<impl::function_name::SUMM, 
    impl::Constanta, fcd::Variable, impl::UnusedParameter> fcd::operator+ (Variable v, impl::Constanta c) noexcept
{
    return impl::summ(c, v);
}

fcd::Variable fcd::operator+ (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Function<impl::function_name::SUMM, 
    fcd::Parameter, fcd::Variable, impl::UnusedParameter> fcd::operator+ (Variable v, Parameter p) noexcept
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

impl::Function<impl::function_name::PRODUCT, 
    fcd::Parameter, fcd::Parameter, impl::UnusedParameter> fcd::operator* (Parameter p1, Parameter p2) noexcept
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

impl::Function<impl::function_name::PRODUCT, 
    impl::Constanta, fcd::Parameter, impl::UnusedParameter> fcd::operator* (impl::Constanta c, Parameter p) noexcept
{
    return impl::product(c, p);
}

impl::Function<impl::function_name::PRODUCT, 
    impl::Constanta, fcd::Variable, impl::UnusedParameter> fcd::operator* (impl::Constanta c, Variable v) noexcept
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

impl::Function<impl::function_name::PRODUCT, 
    impl::Constanta, fcd::Parameter, impl::UnusedParameter> fcd::operator* (Parameter p, impl::Constanta c) noexcept
{
    return impl::product(c, p);
}

impl::ZeroConstanta fcd::operator* (Parameter p, impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}

impl::Function<impl::function_name::PRODUCT, 
    fcd::Parameter, fcd::Variable, impl::UnusedParameter> fcd::operator* (Parameter p, Variable v) noexcept
{
    return impl::product(p, v);
}

impl::Function<impl::function_name::PRODUCT, 
    impl::Constanta, fcd::Variable, impl::UnusedParameter> fcd::operator* (Variable v, impl::Constanta c) noexcept
{
    return impl::product(c, v);
}

impl::ZeroConstanta fcd::operator* (Variable v, impl::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}

impl::Function<impl::function_name::PRODUCT, 
    fcd::Parameter, fcd::Variable, impl::UnusedParameter> fcd::operator* (Variable v, Parameter p) noexcept
{
    return impl::product(p, v);
}

