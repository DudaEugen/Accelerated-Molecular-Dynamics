#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T

#include <cstdint>

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    struct Parameter
    {
        const std::uint8_t index;

        static constexpr bool is_constanta = false;
        static constexpr bool is_contain_variable = false;
        static constexpr bool is_contain_parameter = true;
        static constexpr bool is_function = false;

        explicit Parameter(std::uint8_t i) noexcept;
        double operator() (double argument) const;
    };

    struct Variable
    {
        static constexpr bool is_constanta = false;
        static constexpr bool is_contain_variable =true;
        static constexpr bool is_contain_parameter = false;
        static constexpr bool is_function = false;

        Variable() = default;
        double operator() (double argument) const noexcept;
    };
}

namespace utils::fcd::implementation
{
    struct Constanta
    {
        const double value;

        static constexpr bool is_constanta = true;
        static constexpr bool is_contain_variable = false;
        static constexpr bool is_contain_parameter = false;
        static constexpr bool is_function = false;

        Constanta(double value) noexcept;
        Constanta(int value) noexcept;
        double operator() (double argument) const noexcept;
    };

    struct ZeroConstanta
    {
        static constexpr bool is_constanta = true;
        static constexpr bool is_contain_variable = false;
        static constexpr bool is_contain_parameter = false;
        static constexpr bool is_function = false;

        ZeroConstanta() = default;
        double operator() (double argument) const noexcept;
    };
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
