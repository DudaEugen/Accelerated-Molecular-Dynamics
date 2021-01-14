#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T

#include "structures.hpp"
#include <cmath>
#include "functions_folding.hpp"

namespace utils::fcd::implementation
{
    template<class T>
    auto derivative_exp(const T& arg) noexcept
    {
        return Function<
            function_name::EXPONENTA, typename T::arg_t, UnusedArgument, UnusedParameter
        >(arg.argument);
    }

    template<class T>
    auto derivative_sin(const T& arg) noexcept
    {
        return Function<
            function_name::COSINUS, typename T::arg_t, UnusedArgument, UnusedParameter
        >(arg.argument);
    }

    template<class T>
    auto derivative_cos(const T& arg) noexcept
    {
        auto sinus = Function<
            function_name::SINUS, typename T::arg_t, UnusedArgument, UnusedParameter
        >(arg.argument);

        return Function<
            function_name::PRODUCT, Constanta, decltype(sinus), UnusedParameter
        >(Constanta(-1), sinus);
    }

    template<class T>
    auto derivative_tg(const T& arg) noexcept
    {
        auto cosinus = Function<
            function_name::COSINUS, typename T::arg_t, UnusedArgument, UnusedParameter
        >(arg.argument);

        return Function<
            function_name::POWER, decltype(cosinus), UnusedArgument, -2
        >(cosinus);
    }

    template<class T>
    auto derivative_exponential(const T& arg) noexcept
    {
        return Function<
            function_name::PRODUCT, Constanta, T, UnusedParameter
        >(Constanta(log(T::template_index)), arg);
    }

    template<class T>
    auto derivative_lg(const T& arg) noexcept
    {
        return Function<
            function_name::POWER, typename T::arg_t, UnusedArgument, -1
        >(arg.argument);
    }

    template<class T>
    auto derivative_pow(const T& arg) noexcept
    {
        if constexpr (T::template_index == 2)
        {
            return Function<
                function_name::PRODUCT, Constanta, typename T::arg_t, UnusedParameter
            >(Constanta(2), arg.argument);
        }
        else
        {
            auto func = Function<
                function_name::POWER, 
                typename T::arg_t,
                UnusedArgument,
                T::template_index - 1
            >(arg.argument);

            return Function<
                function_name::PRODUCT, Constanta, decltype(func), UnusedParameter
            >(Constanta(T::template_index), func);
        }
    }

    template<class T>
    auto derivative_root(const T& arg) noexcept
    {
        auto func = Function<
            function_name::POWER, T, UnusedArgument, 1 - T::template_index
        >(arg);

        return Function<
            function_name::PRODUCT, Constanta, decltype(func), UnusedParameter
        >(Constanta(1./(T::template_index)), func);
    }

    template<class T>
    auto derivative_no_function(const T& arg) noexcept
    {
        if constexpr (std::is_same_v<std::decay_t<T>, Variable>)
        {
            return Constanta(1);
        }
        else
        {
            return ZeroConstanta();
        }
    }

    template<class T>
    auto derivative_of_one_argument_function(const T& arg) noexcept
    {
        if constexpr (T::name == function_name::EXPONENTA)
            return derivative_exp(arg);
        else if constexpr (T::name == function_name::POWER)
            return derivative_pow(arg);
        else if constexpr (T::name == function_name::ROOT)
            return derivative_root(arg);
        else if constexpr (T::name == function_name::COSINUS)
            return derivative_cos(arg);
        else if constexpr (T::name == function_name::SINUS)
            return derivative_sin(arg);
        else if constexpr (T::name == function_name::TANGENT)
            return derivative_tg(arg);
        else if constexpr (T::name == function_name::EXPONENTIAL)
            return derivative_exponential(arg);
        else if constexpr (T::name == function_name::LOGARITHM_NATURAL)
            return derivative_lg(arg);
    }
}

namespace utils::fcd
{
    template<class T>
    auto derivative(const T& func_struct)
    {
        using namespace implementation;

        if constexpr (!T::is_function)
        {
            return derivative_no_function(func_struct);
        }
        else if constexpr (T::type == function_type::ONE_ARGUMENT ||
                           T::type == function_type::INDEXED_ONE_ARGUMENT)
        {
            return Function<
                function_name::PRODUCT,
                decltype(derivative_of_one_argument_function(func_struct)),
                decltype(derivative(func_struct.argument)),
                UnusedParameter
            >(derivative_of_one_argument_function(func_struct), derivative(func_struct.argument));
        }
        else if constexpr (T::type == function_type::TWO_ARGUMENT)
        {
            if constexpr (T::name == function_name::PRODUCT)
            {
                auto first_arg = product_by_zero_folding(Function<
                    function_name::PRODUCT,
                    decltype(derivative(func_struct.argument1)),
                    decltype(func_struct.argument2),
                    UnusedParameter
                >(derivative(func_struct.argument1), func_struct.argument2));

                auto second_arg = product_by_zero_folding(Function<
                    function_name::PRODUCT,
                    decltype(func_struct.argument1),
                    decltype(derivative(func_struct.argument2)),
                    UnusedParameter
                >(func_struct.argument1, derivative(func_struct.argument2)));

                return summ_with_zero_folding(Function<
                    function_name::SUMM, decltype(first_arg), decltype(second_arg), UnusedParameter
                >(first_arg, second_arg));
            }
            else if constexpr (T::name == function_name::SUMM)
            {
                return const_function_folding(summ_with_zero_folding(Function<
                    function_name::SUMM,
                    decltype(derivative(func_struct.argument1)),
                    decltype(derivative(func_struct.argument2)),
                    UnusedParameter
                >(derivative(func_struct.argument1), derivative(func_struct.argument2))));
            }
        }
    }

    template<std::uint8_t I, class T>
    auto derivative(const T& func_struct)
    {
        if constexpr (I == 0)
            return func_struct;
        else
            return derivative<I-1>(derivative(func_struct));
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
