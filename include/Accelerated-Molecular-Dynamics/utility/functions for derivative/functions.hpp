#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include "internal using/classes.hpp"

template<class T=double>
auto f_var()
{
    return Variable<T>();
}

template<class T=double>
auto f_param(const uint8_t index) 
{ 
    return Parameter<T>(index); 
}

template<class F, class S>
auto f_sum(const F& first, const S& second) noexcept 
{ 
    return const_folding<Sum, F, S>(first, second);
}

template<class F, class S>
auto f_product(const F& first, const S& second) noexcept 
{
    return const_folding<Product, F, S>(first, second);
}

template<class T>
auto f_exp(const T& v) noexcept 
{ 
    return const_folding<Exp, T>(v);
}

template<class T>
auto f_pow(const T& v, const float p) noexcept 
{
    if constexpr (T::is_const)
        return Const(Pow<T>(v, p).compute_value(0));
    else
        return Pow<T>(v, p); 
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_H
