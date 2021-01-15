#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T

#include <cmath>
#include <utility>
#include <type_traits>
#include "argument.hpp"

namespace utils::fcd::implementation
{
    enum class FunctionName
    {
        Exponenta,
        Sinus,
        Cosinus,
        Tangent,
        LogarithmNatural,
        Power,
        Root,
        Exponential,
        Summ,
        Product,
    };

    enum class FunctionType
    {
        OneArgument,
        TwoArgument,
        IndexedOneArgument,
    };

    struct UnusedArgument;
    constexpr int UnusedParameter = 0;

    template<FunctionName FName, class FirstArgument, class SecondArgument, int Index>
    struct Function;

    template<class T>
    struct Function<FunctionName::Exponenta, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Exponenta;
        static constexpr auto Type = FunctionType::OneArgument;
        static constexpr int TemplateIndex = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return exp(argument(arg));
        }
    };

    template<class T>
    struct Function<FunctionName::Sinus, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Sinus;
        static constexpr auto Type = FunctionType::OneArgument;
        static constexpr int TemplateIndex = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return sin(argument(arg));
        }
    };

    template<class T>
    struct Function<FunctionName::Cosinus, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Cosinus;
        static constexpr auto Type = FunctionType::OneArgument;
        static constexpr int TemplateIndex = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return cos(argument(arg));
        }
    };

    template<class T>
    struct Function<FunctionName::Tangent, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Tangent;
        static constexpr auto Type = FunctionType::OneArgument;
        static constexpr int TemplateIndex = UnusedParameter;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            return tan(argument(arg));
        }
    };

    template<class T>
    struct Function<FunctionName::LogarithmNatural, T, UnusedArgument, UnusedParameter>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::LogarithmNatural;
        static constexpr auto Type = FunctionType::OneArgument;
        static constexpr int TemplateIndex = UnusedParameter;

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
    struct Function<FunctionName::Power, T, UnusedArgument, I>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Power;
        static constexpr auto Type = FunctionType::IndexedOneArgument;
        static constexpr int TemplateIndex = I;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I != 0 && I != 1, "Power can't be equal 0 or 1");
            return pow(argument(arg), I);
        }
    };

    template<class T, int I>
    struct Function<FunctionName::Root, T, UnusedArgument, I>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Root;
        static constexpr auto Type = FunctionType::IndexedOneArgument;
        static constexpr int TemplateIndex = I;

        Function(const T& arg) noexcept : argument{ arg }
        {
        }

        double operator() (double arg) const
        {
            static_assert(I > 1, "Root must be great that 1");
            if constexpr (I == 2)
                return sqrt(argument(arg));
            else if constexpr (I == 3)
                return cbrt(argument(arg));
            else
                return pow(argument(arg), 1./I);
        }
    };

    // I is base degree, argument (T) is exponent
    template<class T, int I>
    struct Function<FunctionName::Exponential, T, UnusedArgument, I>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsConstanta = T::IsConstanta;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Exponential;
        static constexpr auto Type = FunctionType::IndexedOneArgument;
        static constexpr int TemplateIndex = I;

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
    struct Function<FunctionName::Summ, First, Second, UnusedParameter>
    {
        const First argument1;
        const Second argument2;

        using ArgT = std::pair<First, Second>;
        static constexpr bool IsConstanta = First::IsConstanta && Second::IsConstanta;
        static constexpr bool IsContainVariable = First::IsContainVariable || 
                                                    Second::IsContainVariable;
        static constexpr bool IsContainParameter = First::IsContainParameter || 
                                                     Second::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Summ;
        static constexpr auto Type = FunctionType::TwoArgument;

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
    struct Function<FunctionName::Product, First, Second, UnusedParameter>
    {
        const First argument1;
        const Second argument2;

        using ArgT = std::pair<First, Second>;
        static constexpr bool IsConstanta = First::IsConstanta && Second::IsConstanta;
        static constexpr bool IsContainVariable = First::IsContainVariable || 
                                                    Second::IsContainVariable;
        static constexpr bool IsContainParameter = First::IsContainParameter || 
                                                     Second::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr auto Name = FunctionName::Product;
        static constexpr auto Type = FunctionType::TwoArgument;

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
