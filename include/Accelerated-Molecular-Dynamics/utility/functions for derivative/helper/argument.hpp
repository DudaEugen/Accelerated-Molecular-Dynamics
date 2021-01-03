#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T

#include <cstdint>
#include <vector>

struct Constanta
{
    const double value;

    Constanta(double value) noexcept;
    double operator() (double argument) const noexcept;
    Constanta set_parameters(const std::vector<double>& params) const noexcept;
};

struct Parameter
{
    const std::uint8_t index;

    Parameter(std::uint8_t i) noexcept;
    double operator() (double argument) const;
    Constanta set_parameters(const std::vector<double>& params) const;
};

struct Variable
{
    Variable() = default;
    double operator() (double argument) const noexcept;
    Variable set_parameters(const std::vector<double>& params) const noexcept;
};

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENT_T
