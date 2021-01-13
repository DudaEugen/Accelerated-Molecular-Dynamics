#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T

#include <cmath>
#include <utility>
#include <type_traits>
#include "argument.hpp"

namespace utils::fcd::implementation
{
    enum class function_name
    {
        EXPONENTA,
        SQUARE_ROOT,
        CUBIC_ROOT,
        SINUS,
        COSINUS,
        TANGENT,
        LOGARITHM_NATURAL,
        POWER,
        ROOT,
        EXPONENTIAL,
        SUMM,
        PRODUCT,
    };

    enum class function_type
    {
        ONE_ARGUMENT,
        TWO_ARGUMENT,
        INDEXED_ONE_ARGUMENT,
    };

    struct UnusedArgument;
    constexpr int UnusedParameter = 0;

    template<function_name Name, class FirstArgument, class SecondArgument, int Index>
    struct Function;

    template<class T>
    struct Function<function_name::EXPONENTA, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::EXPONENTA;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return exp(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::SQUARE_ROOT, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::SQUARE_ROOT;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return sqrt(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::CUBIC_ROOT, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::CUBIC_ROOT;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return cbrt(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::SINUS, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::SINUS;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return sin(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::COSINUS, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::COSINUS;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return cos(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::TANGENT, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::TANGENT;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return tan(argument(arg));
        }
    };

    template<class T>
    struct Function<function_name::LOGARITHM_NATURAL, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::LOGARITHM_NATURAL;
        static constexpr auto type = function_type::ONE_ARGUMENT;
        static constexpr int template_index = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return log(argument(arg));
        }
    };

    // I is exponent, argument (T) is base degree
    template<class T, int I>
    struct Function<function_name::POWER, T, UnusedArgument, I>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::POWER;
        static constexpr auto type = function_type::INDEXED_ONE_ARGUMENT;
        static constexpr int template_index = I;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I != 0 && I != 1, "power can't be equal 0 or 1");
            return pow(argument(arg), I);
        }
    };

    template<class T, int I>
    struct Function<function_name::ROOT, T, UnusedArgument, I>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::ROOT;
        static constexpr auto type = function_type::INDEXED_ONE_ARGUMENT;
        static constexpr int template_index = I;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I > 1, "root must be great that 1");
            return pow(argument(arg), 1./I);
        }
    };

    // I is base degree, argument (T) is exponent
    template<class T, int I>
    struct Function<function_name::EXPONENTIAL, T, UnusedArgument, I>
    {
        const T argument;

        using arg_t = T;
        static constexpr bool is_constanta = T::is_constanta;
        static constexpr bool is_contain_variable = T::is_contain_variable;
        static constexpr bool is_contain_parameter = T::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::EXPONENTIAL;
        static constexpr auto type = function_type::INDEXED_ONE_ARGUMENT;
        static constexpr int template_index = I;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I > 1, "base of degree must be greater than 1");
            return pow(I, argument(arg));
        }
    };

    template<class First, class Second>
    struct Function<function_name::SUMM, First, Second, UnusedParameter>
    {
        const First argument1;
        const Second argument2;

        using arg_t = std::pair<First, Second>;
        static constexpr bool is_constanta = First::is_constanta && Second::is_constanta;
        static constexpr bool is_contain_variable = First::is_contain_variable || 
                                                    Second::is_contain_variable;
        static constexpr bool is_contain_parameter = First::is_contain_parameter || 
                                                     Second::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::SUMM;
        static constexpr auto type = function_type::TWO_ARGUMENT;

        Function(const First& first, const Second& second) noexcept
            : argument1{ first }, argument2{ second }
        {
        }

        double operator() (double arg) const
        {
            return argument1(arg) + argument2(arg);
        }
    };

    template<class First, class Second>
    struct Function<function_name::PRODUCT, First, Second, UnusedParameter>
    {
        const First argument1;
        const Second argument2;

        using arg_t = std::pair<First, Second>;
        static constexpr bool is_constanta = First::is_constanta && Second::is_constanta;
        static constexpr bool is_contain_variable = First::is_contain_variable || 
                                                    Second::is_contain_variable;
        static constexpr bool is_contain_parameter = First::is_contain_parameter || 
                                                     Second::is_contain_parameter;
        static constexpr bool is_function = true;
        static constexpr auto name = function_name::PRODUCT;
        static constexpr auto type = function_type::TWO_ARGUMENT;

        Function(const First& first, const Second& second) noexcept
            : argument1{ first }, argument2{ second }
        {
        }

        double operator() (double arg) const
        {
            return argument1(arg) * argument2(arg);
        }
    };
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
