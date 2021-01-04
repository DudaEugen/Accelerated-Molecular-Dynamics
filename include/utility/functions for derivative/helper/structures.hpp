#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T

#include <utility>
#include "argument.hpp"

enum class one_arg_function
{
    EXPONENTA,
    SQUARE_ROOT,
};

enum class one_arg_int_template_par_function
{
    POWER,
    ROOT,
};

enum class two_arg_function
{
    SUMM,
    PRODUCT,
};

template<one_arg_function F, class T>
struct OneArgumentFunction;

template<one_arg_int_template_par_function F, class T, int I>
struct OneArgumentIntTemplateParFunction;

template<two_arg_function F, class First, class Second>
struct TwoArgumentFunction;

template<class T>
struct OneArgumentFunction<one_arg_function::EXPONENTA, T>
{
    const T argument;

    using arg_t = T;
    static constexpr auto function_t = one_arg_function::EXPONENTA;

    OneArgumentFunction(const T& arg) noexcept : argument{ arg }
    {
    }

    double operator() (double arg) const
    {
        return exp(argument(arg));
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return OneArgumentFunction<
            function_t, decltype(argument.set_parameters(params))
        >(argument.set_parameters(params));
    }
};

template<class T>
struct OneArgumentFunction<one_arg_function::SQUARE_ROOT, T>
{
    const T argument;

    using arg_t = T;
    static constexpr auto function_t = one_arg_function::SQUARE_ROOT;

    OneArgumentFunction(const T& arg) noexcept : argument{ arg }
    {
    }

    double operator() (double arg) const
    {
        return sqrt(argument(arg));
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return OneArgumentFunction<
            function_t, decltype(argument.set_parameters(params))
        >(argument.set_parameters(params));
    }
};

template<class T, int I>
struct OneArgumentIntTemplateParFunction<one_arg_int_template_par_function::POWER, T, I>
{
    const T argument;

    using arg_t = T;
    static constexpr auto function_t = one_arg_int_template_par_function::POWER;
    static constexpr auto template_index = I;

    OneArgumentIntTemplateParFunction(const T& arg) noexcept 
        : argument{ arg }
    {
    }

    double operator() (double arg) const
    {
        static_assert(I != 0 && I != 1, "power can't be equal 0 or 1");
        return pow(argument(arg), I);
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return OneArgumentIntTemplateParFunction<
            function_t, decltype(argument.set_parameters(params)), I
        >(argument.set_parameters(params));
    }
};

template<class T, int I>
struct OneArgumentIntTemplateParFunction<one_arg_int_template_par_function::ROOT, T, I>
{
    const T argument;

    using arg_t = T;
    static constexpr auto function_t = one_arg_int_template_par_function::ROOT;
    static constexpr auto template_index = I;

    OneArgumentIntTemplateParFunction(const T& arg) noexcept 
        : argument{ arg }
    {
    }

    double operator() (double arg) const
    {
        static_assert(I > 1, "root must be great that 1");
        return pow(argument(arg), 1./I);
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return OneArgumentIntTemplateParFunction<
            function_t, decltype(argument.set_parameters(params)), I
        >(argument.set_parameters(params));
    }
};

template<class First, class Second>
struct TwoArgumentFunction<two_arg_function::SUMM, First, Second>
{
    const First argument1;
    const Second argument2;

    using arg_t = std::pair<First, Second>;
    static constexpr auto function_t = two_arg_function::SUMM;

    TwoArgumentFunction(const First& first, const Second& second) noexcept
        : argument1{ first }, argument2{ second }
    {
    }

    double operator() (double arg) const
    {
        return argument1(arg) + argument2(arg);
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return TwoArgumentFunction<
            function_t, 
            decltype(argument1.set_parameters(params)), 
            decltype(argument2.set_parameters(params))
        >(argument1.set_parameters(params), argument2.set_parameters(params));
    }
};

template<class First, class Second>
struct TwoArgumentFunction<two_arg_function::PRODUCT, First, Second>
{
    const First argument1;
    const Second argument2;

    using arg_t = std::pair<First, Second>;
    static constexpr auto function_t = two_arg_function::PRODUCT;

    TwoArgumentFunction(const First& first, const Second& second) noexcept
        : argument1{ first }, argument2{ second }
    {
    }

    double operator() (double arg) const 
    {
        return argument1(arg) * argument2(arg);
    }

    auto set_parameters(const std::vector<double>& params) const
    {
        return TwoArgumentFunction<
            function_t, 
            decltype(argument1.set_parameters(params)), 
            decltype(argument2.set_parameters(params))
        >(argument1.set_parameters(params), argument2.set_parameters(params));
    }
};

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
