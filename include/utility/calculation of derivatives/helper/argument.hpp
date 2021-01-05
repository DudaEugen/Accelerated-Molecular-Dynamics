#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T

#include <cstdint>

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    struct Constanta
    {
        const double value;

        static constexpr bool is_constanta = true;
        static constexpr bool is_contain_variable = false;

        Constanta(double value) noexcept;
        double operator() (double argument) const noexcept;
    };

    struct Parameter
    {
        const std::uint8_t index;

        static constexpr bool is_constanta = false;
        static constexpr bool is_contain_variable = false;

        Parameter(std::uint8_t i) noexcept;
        double operator() (double argument) const;
    };

    struct Variable
    {
        static constexpr bool is_constanta = false;
        static constexpr bool is_contain_variable =true;

        Variable() = default;
        double operator() (double argument) const noexcept;
    };
}

namespace utils::fcd::implementation
{
    struct ZeroConstanta
    {
        static constexpr bool is_constanta = true;
        static constexpr bool is_contain_variable = false;

        ZeroConstanta() = default;
        double operator() (double argument) const noexcept;
    };
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
