#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T

#include "argument.hpp"
#include "structures.hpp"

namespace utils::fcd::implementation
{
    template<class T>
    auto product_by_zero_folding(const T& func) noexcept
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(func.argument1)>, ZeroConstanta> || 
                      std::is_same_v<std::decay_t<decltype(func.argument2)>, ZeroConstanta>)
            return ZeroConstanta();
        else
            return func;
    }

    template<class T>
    auto summ_with_zero_folding(const T& func) noexcept
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(func.argument1)>, ZeroConstanta>)
            return func.argument2;
        else if constexpr (std::is_same_v<std::decay_t<decltype(func.argument2)>, ZeroConstanta>)
            return func.argument1;
        else
            return func;
    }

    template<class T>
    auto const_function_folding(const T& func)
    {
        if constexpr (!T::is_function)
            return func;
        else if constexpr (T::is_constanta)
            return Constanta(func(0));
        else
            return func;
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
