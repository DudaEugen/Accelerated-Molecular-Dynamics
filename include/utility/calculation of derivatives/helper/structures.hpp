#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T

#include <utility>
#include <type_traits>
#include "argument.hpp"

namespace utils::fcd::implementation
{
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
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;

        OneArgumentFunction(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return exp(argument(arg));
        }
    };

    template<class T>
    struct OneArgumentFunction<one_arg_function::SQUARE_ROOT, T>
    {
        const T argument;

        using arg_t = T;
        static constexpr auto function_t = one_arg_function::SQUARE_ROOT;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;

        OneArgumentFunction(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return sqrt(argument(arg));
        }
    };

    // I is exponent, argument (T) is base degree
    template<class T, int I>
    struct OneArgumentIntTemplateParFunction<one_arg_int_template_par_function::POWER, T, I>
    {
        const T argument;

        using arg_t = T;
        static constexpr auto function_t = one_arg_int_template_par_function::POWER;
        static constexpr auto template_index = I;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;

        OneArgumentIntTemplateParFunction(const T& arg) noexcept 
            : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I != 0 && I != 1, "power can't be equal 0 or 1");
            return pow(argument(arg), I);
        }
    };

    template<class T, int I>
    struct OneArgumentIntTemplateParFunction<one_arg_int_template_par_function::ROOT, T, I>
    {
        const T argument;

        using arg_t = T;
        static constexpr auto function_t = one_arg_int_template_par_function::ROOT;
        static constexpr auto template_index = I;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;

        OneArgumentIntTemplateParFunction(const T& arg) noexcept 
            : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I > 1, "root must be great that 1");
            return pow(argument(arg), 1./I);
        }
    };

    template<class First, class Second>
    struct TwoArgumentFunction<two_arg_function::SUMM, First, Second>
    {
        const First argument1;
        const Second argument2;

        using arg_t = std::pair<First, Second>;
        static constexpr auto function_t = two_arg_function::SUMM;
        static constexpr bool is_constanta = First::is_constanta && Second::is_constanta;
        static constexpr bool is_contain_variable = First::is_contain_variable || Second::is_contain_variable;

        TwoArgumentFunction(const First& first, const Second& second) noexcept
            : argument1{ first }, argument2{ second }
        {
        }

        double operator() (double arg) const
        {
            return argument1(arg) + argument2(arg);
        }
    };

    template<class First, class Second>
    struct TwoArgumentFunction<two_arg_function::PRODUCT, First, Second>
    {
        const First argument1;
        const Second argument2;

        using arg_t = std::pair<First, Second>;
        static constexpr auto function_t = two_arg_function::PRODUCT;
        static constexpr bool is_constanta = First::is_constanta && Second::is_constanta;
        static constexpr bool is_contain_variable = First::is_contain_variable || Second::is_contain_variable;

        TwoArgumentFunction(const First& first, const Second& second) noexcept
            : argument1{ first }, argument2{ second }
        {
        }

        double operator() (double arg) const 
        {
            return argument1(arg) * argument2(arg);
        }
    };

    template<class T>
    constexpr bool is_function_fcd = !(std::is_same_v<std::decay_t<T>, Constanta> || 
                                     std::is_same_v<std::decay_t<T>, ZeroConstanta> ||
                                     std::is_same_v<std::decay_t<T>, Parameter> || 
                                     std::is_same_v<std::decay_t<T>, Variable>);
    
    template<class T>
    constexpr bool is_one_argument_function = is_function_fcd<T> && 
            std::is_same_v<std::decay_t<decltype(T::function_t)>, one_arg_function>;
    
    template<class T>
    constexpr bool is_one_argument_int_template_par_function = is_function_fcd<T> && 
            std::is_same_v<std::decay_t<decltype(T::function_t)>, one_arg_int_template_par_function>;
    
    template<class T>
    constexpr bool is_two_argument_function = is_function_fcd<T> && 
            std::is_same_v<std::decay_t<decltype(T::function_t)>, two_arg_function>;

    template<class T>
    constexpr bool is_contain_parameter = std::is_same_v<std::decay_t<T>, Parameter> ||
            (!T::is_constanta && !T::is_contain_variable);
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
