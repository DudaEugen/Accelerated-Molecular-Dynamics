#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T

#include "Argument.hpp"
#include "Structures.hpp"

namespace utils::fcd::implementation
{
    template<class T>
    constexpr auto productByZeroFolding(const T& func) noexcept
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(func.argument1)>, ZeroConstanta> || 
                      std::is_same_v<std::decay_t<decltype(func.argument2)>, ZeroConstanta>)
            return ZeroConstanta();
        else
            return func;
    }

    template<class T>
    constexpr auto summWithZeroFolding(const T& func) noexcept
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(func.argument1)>, ZeroConstanta>)
            return func.argument2;
        else if constexpr (std::is_same_v<std::decay_t<decltype(func.argument2)>, ZeroConstanta>)
            return func.argument1;
        else
            return func;
    }

    template<class T>
    constexpr auto constFunctionFolding(const T& func)
    {
        if constexpr (!T::IsFunction)
            return func;
        else if constexpr (T::IsConstanta)
            return Constanta(func(0));
        else
            return func;
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FOLDING_T
