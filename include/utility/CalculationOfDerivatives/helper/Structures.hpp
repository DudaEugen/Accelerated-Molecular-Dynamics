#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T

#include <cmath>
#include <utility>
#include <type_traits>
#include "Argument.hpp"

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
        HeavisideStep,
        Summ,
        Product,
        DynamicSumm,
    };

    enum class FunctionType
    {
        OneArgument,
        TwoArgument,
        IndexedOneArgument,
        DynamicOneArgument,
    };

    struct UnusedArgument;
    constexpr int UnusedParameter = 0;

    template<FunctionName FName, class First, class Second, int Index>
    struct FunctionBase
    {
        const First argument1;
        const Second argument2;

        using ArgT = std::pair<First, Second>;
        static constexpr bool IsContainVariable = First::IsContainVariable || 
                                                    Second::IsContainVariable;
        static constexpr bool IsContainParameter = First::IsContainParameter || 
                                                     Second::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr FunctionName Name = FName;
        static constexpr int TemplateIndex = Index;
    };

    template<FunctionName FName, class T, int Index>
    struct FunctionBase<FName, T, UnusedArgument, Index>
    {
        const T argument;

        using ArgT = T;
        static constexpr bool IsContainVariable = T::IsContainVariable;
        static constexpr bool IsContainParameter = T::IsContainParameter;
        static constexpr bool IsFunction = true;
        static constexpr FunctionName Name = FName;
        static constexpr int TemplateIndex = Index;
    };

    template<FunctionName FName, class First, class Second, int Index>
    struct DynamicFunction: FunctionBase<FName, First, Second, Index>
    {
        static constexpr bool IsDynamicFunction = true;
        static constexpr bool IsConstanta = false;
    };

    template<FunctionName FName, class First, class Second, int Index>
    struct NoDynamicFunction: FunctionBase<FName, First, Second, Index>
    {
        static constexpr bool IsDynamicFunction = false;
        static constexpr bool IsConstanta = First::IsConstanta && Second::IsConstanta;

        NoDynamicFunction(const First& first, const Second& second) noexcept
            : NoDynamicFunction::FunctionBase{ first, second }
        {
        }
    };

    template<FunctionName FName, class T, int Index>
    struct NoDynamicFunction<FName, T, UnusedArgument, Index>: FunctionBase<FName, T, UnusedArgument, Index>
    {
        static constexpr bool IsDynamicFunction = false;
        static constexpr bool IsConstanta = T::IsConstanta;

        NoDynamicFunction(const T& arg) noexcept : NoDynamicFunction::FunctionBase{ arg } {}
    };

    template<FunctionName FName, class FirstArgument, class SecondArgument, int Index>
    struct Function;

    // functions
    
    template<class T>
    struct Function<FunctionName::Exponenta, T, UnusedArgument, UnusedParameter>: 
        NoDynamicFunction<FunctionName::Exponenta, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return exp(this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return exp(this->argument(arg, dynamicParameterValue));
        }
    };

    template<class T>
    struct Function<FunctionName::Sinus, T, UnusedArgument, UnusedParameter>:
        NoDynamicFunction<FunctionName::Sinus, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return sin(this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return sin(this->argument(arg, dynamicParameterValue));
        }
    };

    template<class T>
    struct Function<FunctionName::Cosinus, T, UnusedArgument, UnusedParameter>:
        NoDynamicFunction<FunctionName::Cosinus, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return cos(this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return cos(this->argument(arg, dynamicParameterValue));
        }
    };

    template<class T>
    struct Function<FunctionName::Tangent, T, UnusedArgument, UnusedParameter>:
        NoDynamicFunction<FunctionName::Tangent, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return tan(this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return tan(this->argument(arg, dynamicParameterValue));
        }
    };

    template<class T>
    struct Function<FunctionName::LogarithmNatural, T, UnusedArgument, UnusedParameter>:
        NoDynamicFunction<FunctionName::LogarithmNatural, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return log(this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return log(this->argument(arg, dynamicParameterValue));
        }
    };

    // I is exponent, argument (T) is base degree
    template<class T, int I>
    struct Function<FunctionName::Power, T, UnusedArgument, I>:
        NoDynamicFunction<FunctionName::Power, T, UnusedArgument, I>
    {
        static constexpr auto Type = FunctionType::IndexedOneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            static_assert(I != 0 && I != 1, "Power can't be equal 0 or 1");
            return pow(this->argument(arg, dynamicParameters), I);
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            static_assert(I != 0 && I != 1, "Power can't be equal 0 or 1");
            return pow(this->argument(arg, dynamicParameterValue), I);
        }
    };

    template<class T, int I>
    struct Function<FunctionName::Root, T, UnusedArgument, I>:
        NoDynamicFunction<FunctionName::Root, T, UnusedArgument, I>
    {
        static constexpr auto Type = FunctionType::IndexedOneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            static_assert(I > 1, "Root must be great that 1");
            if constexpr (I == 2)
                return sqrt(this->argument(arg, dynamicParameters));
            else if constexpr (I == 3)
                return cbrt(this->argument(arg, dynamicParameters));
            else
                return pow(this->argument(arg, dynamicParameters), 1./I);
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            static_assert(I > 1, "Root must be great that 1");
            if constexpr (I == 2)
                return sqrt(this->argument(arg, dynamicParameterValue));
            else if constexpr (I == 3)
                return cbrt(this->argument(arg, dynamicParameterValue));
            else
                return pow(this->argument(arg, dynamicParameterValue), 1./I);
        }
    };

    // I is base degree, argument (T) is exponent
    template<class T, int I>
    struct Function<FunctionName::Exponential, T, UnusedArgument, I>:
        NoDynamicFunction<FunctionName::Exponential, T, UnusedArgument, I>
    {
        static constexpr auto Type = FunctionType::IndexedOneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            static_assert(I > 1, "base of degree must be greater than 1");
            return pow(I, this->argument(arg, dynamicParameters));
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            static_assert(I > 1, "base of degree must be greater than 1");
            return pow(I, this->argument(arg, dynamicParameterValue));
        }
    };

    template<class T>
    struct Function<FunctionName::HeavisideStep, T, UnusedArgument, UnusedParameter>:
        NoDynamicFunction<FunctionName::HeavisideStep, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::OneArgument;

        Function(const T& arg) noexcept : Function::NoDynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return this->argument(arg, dynamicParameters) > 0 ? 1 : 0;
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return this->argument(arg, dynamicParameterValue) > 0 ? 1 : 0;
        }
    };

    template<class First, class Second>
    struct Function<FunctionName::Summ, First, Second, UnusedParameter>:
        NoDynamicFunction<FunctionName::Summ, First, Second, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::TwoArgument;

        Function(const First& first, const Second& second) noexcept
            : Function::NoDynamicFunction{ first, second }
        {
        }

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return this->argument1(arg, dynamicParameters) + this->argument2(arg, dynamicParameters);
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return this->argument1(arg, dynamicParameterValue) + this->argument2(arg, dynamicParameterValue);
        }
    };

    template<class First, class Second>
    struct Function<FunctionName::Product, First, Second, UnusedParameter>:
        NoDynamicFunction<FunctionName::Product, First, Second, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::TwoArgument;

        Function(const First& first, const Second& second) noexcept
            : Function::NoDynamicFunction{ first, second }
        {
        }

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            return this->argument1(arg, dynamicParameters) * this->argument2(arg, dynamicParameters);
        }

        double operator() (double arg, double dynamicParameterValue) const
        {
            return this->argument1(arg, dynamicParameterValue) * this->argument2(arg, dynamicParameterValue);
        }
    };

    template<class T>
    struct Function<FunctionName::DynamicSumm, T, UnusedArgument, UnusedParameter>:
        DynamicFunction<FunctionName::DynamicSumm, T, UnusedArgument, UnusedParameter>
    {
        static constexpr auto Type = FunctionType::DynamicOneArgument;

        Function(const T& arg) noexcept : Function::DynamicFunction{ arg } {}

        double operator() (double arg, const std::vector<double>* dynamicParameters = nullptr) const
        {
            if (dynamicParameters == nullptr)
                throw std::runtime_error("Miss values for DynamicParameter");

            double result = 0;
            for (double param: *dynamicParameters)
            {
                result += this->argument(arg, param);
            }
            return result;
        }
    };
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_STRUCTURE_T
