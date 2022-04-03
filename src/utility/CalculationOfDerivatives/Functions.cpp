#include "CalculationOfDerivatives/Functions.hpp"

namespace fcd = utils::fcd;
namespace impl = utils::fcd::implementation;

impl::Constanta fcd::operator- (impl::Constanta c) noexcept
{
    return impl::Constanta(-c(0));
}
    
impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator- (Variable v) noexcept
{
    return impl::product(impl::Constanta(-1), v);
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator- (fcd::DynamicParameter v) noexcept
{
    return impl::product(impl::Constanta(-1), v);
}


impl::Constanta fcd::operator+ (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) + c2(0));
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator+ (Variable v1, Variable v2) noexcept
{
    return impl::product(impl::Constanta(2), Variable());
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator+ (fcd::DynamicParameter v1, 
                                                                        fcd::DynamicParameter v2) noexcept
{
    return impl::product(impl::Constanta(2), DynamicParameter());
}

impl::Constanta fcd::operator+ (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return c1;
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator+ (impl::Constanta c, Variable v) noexcept
{
    return impl::summ(c, v);
}

impl::Summ_t<impl::Constanta, fcd::DynamicParameter> fcd::operator+ (impl::Constanta c, 
                                                                     fcd::DynamicParameter v) noexcept
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

fcd::DynamicParameter fcd::operator+ (impl::ZeroConstanta c, fcd::DynamicParameter v) noexcept
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

impl::Summ_t<fcd::DynamicParameter, fcd::Variable> fcd::operator+ (fcd::Variable v, 
                                                                   fcd::DynamicParameter p) noexcept
{
    return impl::summ(p, v);
}

impl::Summ_t<impl::Constanta, fcd::DynamicParameter> fcd::operator+ (fcd::DynamicParameter p, 
                                                                     impl::Constanta c) noexcept
{
    return impl::summ(c, p);
}
    
fcd::DynamicParameter fcd::operator+ (fcd::DynamicParameter p, impl::ZeroConstanta c) noexcept
{
    return DynamicParameter();
}

impl::Summ_t<fcd::DynamicParameter, fcd::Variable> fcd::operator+ (fcd::DynamicParameter p, 
                                                                   fcd::Variable v) noexcept
{
    return impl::summ(p, v);
}


impl::Constanta fcd::operator* (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0)*c2(0));
}

impl::Function<impl::FunctionName::Power, 
    fcd::Variable, impl::UnusedArgument, 2> fcd::operator* (Variable v1, Variable v2) noexcept
{
    return power<2>(Variable());
}

impl::Function<impl::FunctionName::Power, fcd::DynamicParameter, impl::UnusedArgument, 2> 
    fcd::operator* (fcd::DynamicParameter p1, fcd::DynamicParameter p2) noexcept
{
    return power<2>(DynamicParameter());
}

impl::ZeroConstanta fcd::operator* (impl::Constanta c1, impl::ZeroConstanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator* (impl::Constanta c, Variable v) noexcept
{
    return impl::product(c, v);
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator* (impl::Constanta c, 
                                                                        fcd::DynamicParameter p) noexcept
{
    return impl::product(c, p);
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator* (impl::ZeroConstanta c, fcd::DynamicParameter v) noexcept
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

impl::Product_t<fcd::DynamicParameter, fcd::Variable> fcd::operator* (fcd::Variable v, 
                                                                      fcd::DynamicParameter p) noexcept
{
    return impl::product(p, v);
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator* (fcd::DynamicParameter p, 
                                                                        impl::Constanta c) noexcept
{
    return impl::product(c, p);
}
    
impl::ZeroConstanta fcd::operator* (DynamicParameter p, implementation::ZeroConstanta c) noexcept
{
    return impl::ZeroConstanta();
}
    
impl::Product_t<fcd::DynamicParameter, fcd::Variable> fcd::operator* (fcd::DynamicParameter p, 
                                                                      fcd::Variable v) noexcept
{
    return impl::product(p, v);
}

impl::Constanta fcd::operator- (impl::Constanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::ZeroConstanta fcd::operator- (Variable v1, Variable v2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator- (fcd::DynamicParameter v1, fcd::DynamicParameter v2) noexcept
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

impl::Difference_t<impl::Constanta, fcd::DynamicParameter> fcd::operator- (impl::Constanta c, 
                                                                           fcd::DynamicParameter p) noexcept
{
    return c + (-p);
}

impl::Constanta fcd::operator- (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::Constanta(c1(0) - c2(0));
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator- (impl::ZeroConstanta c, Variable v) noexcept
{
    return -v;
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator- (impl::ZeroConstanta c, 
                                                                        fcd::DynamicParameter p) noexcept
{
    return -p;
}

impl::Summ_t<impl::Constanta, fcd::Variable> fcd::operator- (Variable v, impl::Constanta c) noexcept
{
    return v + (-c);
}

fcd::Variable fcd::operator- (Variable v, impl::ZeroConstanta c) noexcept
{
    return v;
}

impl::Summ_t<fcd::DynamicParameter, impl::Product_t<impl::Constanta, fcd::Variable>> 
    fcd::operator- (fcd::Variable v, fcd::DynamicParameter c) noexcept
{
    return c + (-v);
}

impl::Summ_t<impl::Constanta, fcd::DynamicParameter> fcd::operator- (fcd::DynamicParameter p, 
                                                                     impl::Constanta c) noexcept
{
    return p + (-c);
}

fcd::DynamicParameter fcd::operator- (fcd::DynamicParameter p, impl::ZeroConstanta c) noexcept
{
    return DynamicParameter();
}


impl::Difference_t<fcd::DynamicParameter, fcd::Variable> 
    fcd::operator- (fcd::DynamicParameter p, fcd::Variable v) noexcept
{
    return p + (-v);
}

impl::Constanta fcd::operator/ (impl::Constanta c1, impl::Constanta c2)
{
    return impl::Constanta(c1(0)/c2(0));
}

impl::Constanta fcd::operator/ (Variable v1, Variable v2) noexcept
{
    return impl::Constanta(1);
}

impl::Constanta fcd::operator/ (fcd::DynamicParameter v1, fcd::DynamicParameter v2) noexcept
{
    return impl::Constanta(1);
}


impl::Ratio_t<impl::Constanta, fcd::Variable> fcd::operator/ (impl::Constanta c, Variable v) noexcept
{
    return c * power<-1>(v);
}

impl::Ratio_t<impl::Constanta, fcd::DynamicParameter> fcd::operator/ (impl::Constanta c, 
                                                                      fcd::DynamicParameter p) noexcept
{
    return c * power<-1>(p);
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c1, impl::Constanta c2) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c, Variable v) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta fcd::operator/ (impl::ZeroConstanta c, fcd::DynamicParameter p) noexcept
{
    return impl::ZeroConstanta();
}

impl::Product_t<impl::Constanta, fcd::Variable> fcd::operator/ (Variable v, impl::Constanta c)
{
    return impl::Constanta(1/c(0)) * v;
}

impl::Ratio_t<fcd::Variable, fcd::DynamicParameter> fcd::operator/ (fcd::Variable v, 
                                                                    fcd::DynamicParameter p) noexcept
{
    return v * power<-1>(p);
}

impl::Product_t<impl::Constanta, fcd::DynamicParameter> fcd::operator/ (fcd::DynamicParameter p, 
                                                                      impl::Constanta c)
{
    return impl::Constanta(1/c(0)) * p;
}

impl::Ratio_t<fcd::DynamicParameter, fcd::Variable> fcd::operator/ (fcd::DynamicParameter p, 
                                                                    fcd::Variable v) noexcept
{
    return p * power<-1>(v);
}
