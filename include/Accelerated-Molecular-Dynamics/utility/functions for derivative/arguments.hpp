#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENTS_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENTS_H

#include <cstdint>
#include <vector>
#include <stdexcept>

template<class T>
class Const;

Const(int) -> Const<double>;

template<class T>
class Variable;

template<class T>
class Parameter;

// default specialisations

template<>
class Const<double>
{
    const double value;
public:
    Const(double v) noexcept
        : value{ v }
    {
    }

    using value_type = double;
    static constexpr bool is_const = true;
    
    const double compute_value(double x) const noexcept { return value; }
    const double compute_derivative(double x) const noexcept { return 0; }

    template<class P>
    const Const& set_parameters(const std::vector<P>& params) const { return *this; };
};

template<>
class Variable<double>
{
public:
    Variable() noexcept = default;

    static constexpr bool is_const = false;

    const double compute_value(const double x) const noexcept { return x; }
    const double compute_derivative(const double x) const noexcept { return 1; }

    template<class P>
    const Variable& set_parameters(const std::vector<P>& params) const
    {
        return *this;
    }
};

template<>
class Parameter<double>
{
    const uint8_t index;
public:
    Parameter(uint8_t i) noexcept
        : index{ i }
    {
    }

    static constexpr bool is_const = false;

    const double compute_value(double x) const
    {
        throw std::runtime_error("class Parameter can't compute value");
    }
    const double compute_derivative(double x) const noexcept { return 0; }

    template<class P>
    Const<P> set_parameters(const std::vector<P>& params) const 
    {
        return Const(params[index]);
    }
};

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_ARGUMENTS_H
