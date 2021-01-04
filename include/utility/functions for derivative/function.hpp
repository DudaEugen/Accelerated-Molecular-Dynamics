#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T

#include "helper/derivative_rules.hpp"

template<class T>
auto f_exp(const T& argument)
{
    return OneArgumentFunction<one_arg_function::EXPONENTA, T>(argument);
}

template<class T>
auto f_sqrt(const T& argument)
{
    return OneArgumentFunction<one_arg_function::SQUARE_ROOT, T>(argument);
}

template<int I, class T>
auto f_pow(const T& argument)
{
    return OneArgumentIntTemplateParFunction<
        one_arg_int_template_par_function::POWER, T, I
    >(argument);
}

template<int I, class T>
auto f_root(const T& argument)
{
    if constexpr (I != 2)
        return OneArgumentIntTemplateParFunction<
            one_arg_int_template_par_function::ROOT, T, I
        >(argument);
    else
        return OneArgumentFunction<one_arg_function::SQUARE_ROOT, T>(argument);    
}

template<class F, class S>
auto f_sum(const F& first, const S& second)
{
    return TwoArgumentFunction<two_arg_function::SUMM, F, S>(first, second);
}

template<class F, class S>
auto f_prod(const F& first, const S& second)
{
    return TwoArgumentFunction<two_arg_function::PRODUCT, F, S>(first, second);
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
