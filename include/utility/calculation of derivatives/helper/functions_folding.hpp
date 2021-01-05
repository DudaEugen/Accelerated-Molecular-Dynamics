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
        if constexpr (std::is_same_v<decltype(func.argument1), const ZeroConstanta> || 
                    std::is_same_v<decltype(func.argument2), const ZeroConstanta>)
            return ZeroConstanta();
        else
            return func;
    }

    template<class T>
    auto summ_with_zero_folding(const T& func) noexcept
    {
        if constexpr (std::is_same_v<decltype(func.argument1), const ZeroConstanta>)
            return func.argument2;
        else if constexpr (std::is_same_v<decltype(func.argument2), const ZeroConstanta>)
            return func.argument1;
        else
            return func;
    }

    template<class T>
    auto const_function_folding(const T& func)
    {
        if constexpr (!is_function_fcd<T>)
            return func;
        else if constexpr (T::is_constanta)
            return Constanta(func(0));
        else
            return func;
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
