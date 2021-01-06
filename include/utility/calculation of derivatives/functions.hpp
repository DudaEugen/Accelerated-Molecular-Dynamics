#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T

#include "helper/set_parameters.hpp"
#include "helper/derivative_rules.hpp"

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    template<class T>
    auto exponenta(const T& argument)
    {
        return implementation::const_function_folding(implementation::Function<
            implementation::function_name::EXPONENTA,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument));
    }

    template<class T>
    auto sq_root(const T& argument)
    {
        return implementation::const_function_folding(implementation::Function<
            implementation::function_name::SQUARE_ROOT, 
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument));
    }

    // I is exponent, argument (T) is base degree
    template<int I, class T>
    auto power(const T& argument)
    {
        return implementation::const_function_folding(implementation::Function<
            implementation::function_name::POWER, T, implementation::UnusedArgument, I
        >(argument));
    }

    template<std::uint8_t I, class T>
    auto root(const T& argument)
    {
        if constexpr (I != 2)
            return implementation::const_function_folding(implementation::Function<
                implementation::function_name::ROOT, T, implementation::UnusedArgument, I
            >(argument));
        else
            return implementation::const_function_folding(implementation::Function<
                implementation::function_name::SQUARE_ROOT, 
                T,
                implementation::UnusedArgument,
                implementation::UnusedParameter
            >(argument));    
    }

    template<class F, class S>
    auto summ(const F& first, const S& second)
    {
        return implementation::const_function_folding(implementation::Function<
            implementation::function_name::SUMM, F, S, implementation::UnusedParameter
        >(first, second));
    }

    template<class F, class S>
    auto product(const F& first, const S& second)
    {
        return implementation::const_function_folding(implementation::Function<
            implementation::function_name::PRODUCT, F, S, implementation::UnusedParameter
        >(first, second));
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
