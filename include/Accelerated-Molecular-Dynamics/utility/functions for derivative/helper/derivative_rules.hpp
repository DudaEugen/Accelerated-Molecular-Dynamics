#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T

#include "structures.hpp"
#include <cmath>
#include "functions_folding.hpp"

ZeroConstanta derivative_arg(ZeroConstanta constanta) noexcept;

ZeroConstanta derivative_arg(Constanta constanta) noexcept;

ZeroConstanta derivative_arg(Parameter parameter) noexcept;

Constanta derivative_arg(Variable variable) noexcept;

template<class T>
auto derivative_exp(const T& arg) noexcept
{
    return OneArgumentFunction<
        one_arg_function::EXPONENTA, typename T::arg_t
    >(arg.argument);
}

template<class T>
auto derivative_sqrt(const T& arg) noexcept
{
    auto func = OneArgumentIntTemplateParFunction<
        one_arg_int_template_par_function::POWER, T, -1
    >(arg);

    return TwoArgumentFunction<
        two_arg_function::PRODUCT, Constanta, decltype(func)
    >(Constanta(0.5), func);
}

template<class T>
auto derivative_pow(const T& arg) noexcept
{
    if constexpr (T::template_index == 2)
    {
        return TwoArgumentFunction<
            two_arg_function::PRODUCT, Constanta, typename T::arg_t
        >(Constanta(2), arg.argument);
    }
    else
    {
        auto func = OneArgumentIntTemplateParFunction<
            one_arg_int_template_par_function::POWER, 
            typename T::arg_t, 
            T::template_index - 1
        >(arg.argument);

        return TwoArgumentFunction<
            two_arg_function::PRODUCT, Constanta, decltype(func)
        >(Constanta(T::template_index), func);
    }
}

template<class T>
auto derivative_root(const T& arg) noexcept
{
    auto func = OneArgumentIntTemplateParFunction<
        one_arg_int_template_par_function::POWER, T, 1 - T::template_index
    >(arg);

    return TwoArgumentFunction<
        two_arg_function::PRODUCT, Constanta, decltype(func)
    >(Constanta(1./(T::template_index)), func);
}

template<class T>
auto derivative(const T& func_struct)
{
    if constexpr (std::is_same_v<T, Constanta> || std::is_same_v<T, ZeroConstanta> || 
                  std::is_same_v<T, Parameter> || std::is_same_v<T, Variable>)
    {
        return derivative_arg(func_struct);
    }
    else if constexpr (std::is_same_v<decltype(T::function_t), const one_arg_function>)
    {
        if constexpr (T::function_t == one_arg_function::EXPONENTA)
        {
            return TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(derivative_exp(func_struct)),
                decltype(derivative(func_struct.argument))
            >(derivative_exp(func_struct), derivative(func_struct.argument));
        }
        else
        {
            return TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(derivative_sqrt(func_struct)),
                decltype(derivative(func_struct.argument))
            >(derivative_sqrt(func_struct), derivative(func_struct.argument));
        }
    }
    else if constexpr (std::is_same_v<decltype(T::function_t), const one_arg_int_template_par_function>)
    {
        if constexpr (T::function_t == one_arg_int_template_par_function::POWER)
        {
            return TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(derivative_pow(func_struct)),
                decltype(derivative(func_struct.argument))
            >(derivative_pow(func_struct), derivative(func_struct.argument));
        }
        else
        {
            return TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(derivative_root(func_struct)),
                decltype(derivative(func_struct.argument))
            >(derivative_root(func_struct), derivative(func_struct.argument));
        }
    }
    else if constexpr (std::is_same_v<decltype(T::function_t), const two_arg_function>)
    {
        if constexpr (T::function_t == two_arg_function::PRODUCT)
        {
            auto first_arg = product_function_folding(TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(derivative(func_struct.argument1)),
                decltype(func_struct.argument2)
            >(derivative(func_struct.argument1), func_struct.argument2));

            auto second_arg = product_function_folding(TwoArgumentFunction<
                two_arg_function::PRODUCT,
                decltype(func_struct.argument1),
                decltype(derivative(func_struct.argument2))
            >(func_struct.argument1, derivative(func_struct.argument2)));

            return summ_function_folding(TwoArgumentFunction<
                two_arg_function::SUMM, decltype(first_arg), decltype(second_arg)
            >(first_arg, second_arg));
        }
        else
        {
            return summ_function_folding(TwoArgumentFunction<
                two_arg_function::SUMM,
                decltype(derivative(func_struct.argument1)),
                decltype(derivative(func_struct.argument2))
            >(derivative(func_struct.argument1), derivative(func_struct.argument2)));
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

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
