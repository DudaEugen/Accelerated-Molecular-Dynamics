#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T

#include "argument.hpp"
#include "structures.hpp"

namespace utils::fcd::implementation
{
    struct ZeroConstanta
    {
        ZeroConstanta() = default;
        double operator() (double argument) const noexcept;
        ZeroConstanta set_parameters(const std::vector<double>& params) const noexcept;
    };

    template<class T>
    auto product_function_folding(const T& func)
    {
        if constexpr (std::is_same_v<decltype(func.argument1), const ZeroConstanta> || 
                    std::is_same_v<decltype(func.argument2), const ZeroConstanta>)
            return ZeroConstanta();
        else
            return func;
    }

    template<class T>
    auto summ_function_folding(const T& func)
    {
        if constexpr (std::is_same_v<decltype(func.argument1), const ZeroConstanta>)
            return func.argument2;
        else if constexpr (std::is_same_v<decltype(func.argument2), const ZeroConstanta>)
            return func.argument1;
        else
            return func;
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
