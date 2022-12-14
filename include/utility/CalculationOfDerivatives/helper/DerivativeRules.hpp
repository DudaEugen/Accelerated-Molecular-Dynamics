#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T

#include "Structures.hpp"
#include <cmath>
#include "FunctionsFolding.hpp"

namespace utils::fcd::implementation
{
    template<class T>
    constexpr auto derivativeExp(const T& arg) noexcept
    {
        return Function<
            FunctionName::Exponenta, typename T::ArgT, UnusedArgument, UnusedParameter
        >(arg.argument);
    }

    template<class T>
    constexpr auto derivativeSin(const T& arg) noexcept
    {
        return Function<
            FunctionName::Cosinus, typename T::ArgT, UnusedArgument, UnusedParameter
        >(arg.argument);
    }

    template<class T>
    constexpr auto derivativeCos(const T& arg) noexcept
    {
        auto sinus = Function<
            FunctionName::Sinus, typename T::ArgT, UnusedArgument, UnusedParameter
        >(arg.argument);

        return Function<
            FunctionName::Product, Constanta, decltype(sinus), UnusedParameter
        >(Constanta(-1), sinus);
    }

    template<class T>
    constexpr auto derivativeTg(const T& arg) noexcept
    {
        auto cosinus = Function<
            FunctionName::Cosinus, typename T::ArgT, UnusedArgument, UnusedParameter
        >(arg.argument);

        return Function<
            FunctionName::Power, decltype(cosinus), UnusedArgument, -2
        >(cosinus);
    }

    template<class T>
    constexpr auto derivativeExponential(const T& arg) noexcept
    {
        return Function<
            FunctionName::Product, Constanta, T, UnusedParameter
        >(Constanta(log(T::TemplateIndex)), arg);
    }

    template<class T>
    constexpr auto derivativeLg(const T& arg) noexcept
    {
        return Function<
            FunctionName::Power, typename T::ArgT, UnusedArgument, -1
        >(arg.argument);
    }

    template<class T>
    constexpr auto derivativePow(const T& arg) noexcept
    {
        if constexpr (T::TemplateIndex == 2)
        {
            return Function<
                FunctionName::Product, Constanta, typename T::ArgT, UnusedParameter
            >(Constanta(2), arg.argument);
        }
        else
        {
            auto func = Function<
                FunctionName::Power, 
                typename T::ArgT,
                UnusedArgument,
                T::TemplateIndex - 1
            >(arg.argument);

            return Function<
                FunctionName::Product, Constanta, decltype(func), UnusedParameter
            >(Constanta(T::TemplateIndex), func);
        }
    }

    template<class T>
    constexpr auto derivativeRoot(const T& arg) noexcept
    {
        auto func = Function<
            FunctionName::Power, T, UnusedArgument, 1 - T::TemplateIndex
        >(arg);

        return Function<
            FunctionName::Product, Constanta, decltype(func), UnusedParameter
        >(Constanta(1./(T::TemplateIndex)), func);
    }

    template<class T>
    constexpr auto derivativeHeavisideStep(const T& arg) noexcept
    {
        return ZeroConstanta();
    }

    template<class T>
    constexpr auto derivativeNoFunction(const T& arg) noexcept
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
    constexpr auto derivativeOneArgumentFunction(const T& arg) noexcept
    {
        if constexpr (T::Name == FunctionName::Exponenta)
            return derivativeExp(arg);
        else if constexpr (T::Name == FunctionName::Power)
            return derivativePow(arg);
        else if constexpr (T::Name == FunctionName::Root)
            return derivativeRoot(arg);
        else if constexpr (T::Name == FunctionName::Cosinus)
            return derivativeCos(arg);
        else if constexpr (T::Name == FunctionName::Sinus)
            return derivativeSin(arg);
        else if constexpr (T::Name == FunctionName::Tangent)
            return derivativeTg(arg);
        else if constexpr (T::Name == FunctionName::Exponential)
            return derivativeExponential(arg);
        else if constexpr (T::Name == FunctionName::LogarithmNatural)
            return derivativeLg(arg);
        else if constexpr (T::Name == FunctionName::HeavisideStep)
            return derivativeHeavisideStep(arg);
    }
}

namespace utils::fcd
{
    template<class T>
    constexpr auto derivative(const T& func_struct)
    {
        using namespace implementation;

        if constexpr (!T::IsFunction)
        {
            return derivativeNoFunction(func_struct);
        }
        else if constexpr (T::Type == FunctionType::OneArgument ||
                           T::Type == FunctionType::IndexedOneArgument)
        {
            if constexpr (std::is_same_v<typename T::ArgT, Variable>)
            {
                return derivativeOneArgumentFunction(func_struct);
            }
            else
            {
                return Function<
                    FunctionName::Product,
                    decltype(derivativeOneArgumentFunction(func_struct)),
                    decltype(derivative(func_struct.argument)),
                    UnusedParameter
                >(derivativeOneArgumentFunction(func_struct), derivative(func_struct.argument));
            }
        }
        else if constexpr (T::Type == FunctionType::TwoArgument)
        {
            if constexpr (T::Name == FunctionName::Product)
            {
                auto first_arg = productByZeroFolding(Function<
                    FunctionName::Product,
                    decltype(derivative(func_struct.argument1)),
                    decltype(func_struct.argument2),
                    UnusedParameter
                >(derivative(func_struct.argument1), func_struct.argument2));

                auto second_arg = productByZeroFolding(Function<
                    FunctionName::Product,
                    decltype(func_struct.argument1),
                    decltype(derivative(func_struct.argument2)),
                    UnusedParameter
                >(func_struct.argument1, derivative(func_struct.argument2)));

                return summWithZeroFolding(Function<
                    FunctionName::Summ, decltype(first_arg), decltype(second_arg), UnusedParameter
                >(first_arg, second_arg));
            }
            else if constexpr (T::Name == FunctionName::Summ)
            {
                return constFunctionFolding(summWithZeroFolding(Function<
                    FunctionName::Summ,
                    decltype(derivative(func_struct.argument1)),
                    decltype(derivative(func_struct.argument2)),
                    UnusedParameter
                >(derivative(func_struct.argument1), derivative(func_struct.argument2))));
            }
        }
        else if constexpr (T::Type == FunctionType::DynamicOneArgument)
        {
            if constexpr (T::Name == FunctionName::DynamicSumm)
            {
                return Function<
                    FunctionName::DynamicSumm,
                    decltype(derivative(func_struct.argument)),
                    UnusedArgument,
                    UnusedParameter
                >(derivative(func_struct.argument));
            }
        }
    }

    template<std::uint8_t I, class T>
    constexpr auto derivative(const T& func_struct)
    {
        if constexpr (I == 0)
            return func_struct;
        else
            return derivative<I-1>(derivative(func_struct));
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_DERIVATIVE_RULES_T
