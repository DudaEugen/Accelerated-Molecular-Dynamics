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

        static constexpr bool IsConstanta = false;
        static constexpr bool IsContainVariable = false;
        static constexpr bool IsContainParameter = true;
        static constexpr bool IsFunction = false;

        explicit Parameter(std::uint8_t i) noexcept;
        double operator() (double argument) const;
    };

    struct Variable
    {
        static constexpr bool IsConstanta = false;
        static constexpr bool IsContainVariable =true;
        static constexpr bool IsContainParameter = false;
        static constexpr bool IsFunction = false;

        Variable() = default;
        double operator() (double argument) const noexcept;
    };
}

namespace utils::fcd::implementation
{
    struct Constanta
    {
        const double value;

        static constexpr bool IsConstanta = true;
        static constexpr bool IsContainVariable = false;
        static constexpr bool IsContainParameter = false;
        static constexpr bool IsFunction = false;

        Constanta(double value) noexcept;
        Constanta(int value) noexcept;
        double operator() (double argument) const noexcept;
    };

    struct ZeroConstanta
    {
        static constexpr bool IsConstanta = true;
        static constexpr bool IsContainVariable = false;
        static constexpr bool IsContainParameter = false;
        static constexpr bool IsFunction = false;

        ZeroConstanta() = default;
        double operator() (double argument) const noexcept;
    };
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
