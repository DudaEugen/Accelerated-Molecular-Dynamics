#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_HELPERS_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_HELPERS_H

#include "../arguments.hpp"

template<template <class> class T, class A>
auto f_const(const A& arg) noexcept 
{ 
    return Const(T<A>(arg).compute_value(0)); 
}

template<template <class, class> class F, class A>
auto f_const(const A& arg1, const A& arg2) noexcept 
{ 
    return Const(F<A, A>(arg1, arg2).compute_value(0)); 
}

template<template <class> class Func, class T>
auto const_folding(const T& argument)
{
    if constexpr (T::is_const)
        return f_const<Func>(argument);
    else
        return Func<T>(argument);
}

template<template <class, class> class Func, class First, class Second>
auto const_folding(const First& first_f, const Second& second_f)
{
    if constexpr (First::is_const && Second::is_const)
        return f_const<Func>(first_f, second_f);
    else
        return Func<First, Second>(first_f, second_f);
}


#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_HELPERS_H
