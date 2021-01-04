#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T

#include "helper/derivative_rules.hpp"

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    template<class T>
    auto exponenta(const T& argument)
    {
        return implementation::OneArgumentFunction<
            implementation::one_arg_function::EXPONENTA, T
        >(argument);
    }

    template<class T>
    auto sq_root(const T& argument)
    {
        return implementation::OneArgumentFunction<
            implementation::one_arg_function::SQUARE_ROOT, T
        >(argument);
    }

    template<int I, class T>
    auto power(const T& argument)
    {
        return implementation::OneArgumentIntTemplateParFunction<
            implementation::one_arg_int_template_par_function::POWER, T, I
        >(argument);
    }

    template<std::uint8_t I, class T>
    auto root(const T& argument)
    {
        if constexpr (I != 2)
            return implementation::OneArgumentIntTemplateParFunction<
                implementation::one_arg_int_template_par_function::ROOT, T, I
            >(argument);
        else
            return implementation::OneArgumentFunction<
                implementation::one_arg_function::SQUARE_ROOT, T
            >(argument);    
    }

    template<class F, class S>
    auto summ(const F& first, const S& second)
    {
        return implementation::TwoArgumentFunction<
            implementation::two_arg_function::SUMM, F, S
        >(first, second);
    }

    template<class F, class S>
    auto product(const F& first, const S& second)
    {
        return implementation::TwoArgumentFunction<
            implementation::two_arg_function::PRODUCT, F, S
        >(first, second);
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
