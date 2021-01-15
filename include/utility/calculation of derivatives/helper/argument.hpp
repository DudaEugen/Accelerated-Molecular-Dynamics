#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T

#include <cstdint>
#include <stdexcept>

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    template<std::uint8_t I>
    struct Parameter
    {
        static constexpr bool IsConstanta = false;
        static constexpr bool IsContainVariable = false;
        static constexpr bool IsContainParameter = true;
        static constexpr bool IsFunction = false;

        Parameter() noexcept = default;
        double operator() (double argument) const
        {
            throw std::runtime_error("Parameter in function for derivative don't initializing!");
        }
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
