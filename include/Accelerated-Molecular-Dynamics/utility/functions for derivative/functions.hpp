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

template<int I, class T>
auto f_pow(const T& v) noexcept
{
    static_assert(I != 0, "power of f_pow can't be equal 0");

    if constexpr (I == 1)
        return v;
    else if constexpr (I == -1)
        if constexpr(T::is_const)
            return Const<typename T::value_type>(v.compute_value(typename T::value_type{}));
        else
            return MinusFirstDegree<T>(v);
    else if constexpr (I > 1)
        if constexpr(T::is_const)
            return Const<typename T::value_type>(
                        UnsignedIntegralPow<T, I>(v).compute_value(typename T::value_type{})
                );
        else
            return UnsignedIntegralPow<T, I>(v);
    else
        if constexpr(T::is_const)
            return Const<typename T::value_type>(MinusFirstDegree<UnsignedIntegralPow<T, -I>>(
                    UnsignedIntegralPow<T, -I>(v)
                ).compute_value(typename T::value_type{}));
        else
            return MinusFirstDegree<UnsignedIntegralPow<T, -I>>(UnsignedIntegralPow<T, -I>(v));
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_H
