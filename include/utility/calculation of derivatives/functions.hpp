#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T

#include "helper/set_parameters.hpp"
#include "helper/derivative_rules.hpp"

namespace utils::fcd::implementation
{
    template<function_name N, class T, class S, int I>
    auto create_function(const T& argument)
    {
        if constexpr (std::is_same_v<T, double> || std::is_same_v<T, int>)
            return implementation::const_function_folding(implementation::Function<
                N, Constanta, S, I
            >(implementation::Constanta{argument}));
        else if constexpr (std::is_same_v<T, Constanta>)
            return implementation::const_function_folding(implementation::Function<
                N, Constanta, S, I
            >(argument));
        else
            return implementation::const_function_folding(implementation::Function<
                N, T, S, I
            >(argument));
    }

    template<class F, class S>
    auto summ(const F& first, const S& second)
    {
        return const_function_folding(Function<
            function_name::SUMM, F, S, implementation::UnusedParameter
        >(first, second));
    }

    template<class F, class S>
    auto product(const F& first, const S& second)
    {
        return const_function_folding(Function<
            function_name::PRODUCT, F, S, implementation::UnusedParameter
        >(first, second));
    }
}

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    implementation::Constanta operator+ (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator+ (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Function<implementation::function_name::SUMM, 
        Parameter, Parameter, implementation::UnusedParameter> operator+ (Parameter p1, Parameter p2) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, implementation::Constanta, 
        Variable, implementation::UnusedParameter> operator+ (Variable v1, Variable v2) noexcept;

    implementation::Constanta operator+ (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Function<implementation::function_name::SUMM, implementation::Constanta, 
        Parameter, implementation::UnusedParameter> operator+ (implementation::Constanta c, Parameter p) noexcept;

    implementation::Function<implementation::function_name::SUMM, implementation::Constanta, 
        Variable, implementation::UnusedParameter> operator+ (implementation::Constanta c, Variable v) noexcept;

    implementation::Constanta operator+ (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    Parameter operator+ (implementation::ZeroConstanta c, Parameter p) noexcept;

    Variable operator+ (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::Function<implementation::function_name::SUMM, implementation::Constanta, 
        Parameter, implementation::UnusedParameter> operator+ (Parameter p, implementation::Constanta c) noexcept;

    Parameter operator+ (Parameter p, implementation::ZeroConstanta c) noexcept;

    implementation::Function<implementation::function_name::SUMM, 
        Parameter, Variable, implementation::UnusedParameter> operator+ (Parameter p, Variable v) noexcept;

    implementation::Function<implementation::function_name::SUMM, implementation::Constanta, 
        Variable, implementation::UnusedParameter> operator+ (Variable v, implementation::Constanta c) noexcept;

    Variable operator+ (Variable v, implementation::ZeroConstanta c) noexcept;

    implementation::Function<implementation::function_name::SUMM, 
        Parameter, Variable, implementation::UnusedParameter> operator+ (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return summ(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return summ(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return func;
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return func;
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, Parameter p)
    {
        return summ(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return summ(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return summ(v, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return summ(v, func);
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator+ (const implementation::Function<N1, F1, S1, I1>& func1, 
                    const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return summ(func1, func2);
    }

    implementation::Constanta operator* (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, 
        Parameter, Parameter, implementation::UnusedParameter> operator* (Parameter p1, Parameter p2) noexcept;

    implementation::Function<implementation::function_name::POWER, 
        Variable, implementation::UnusedArgument, 2> operator* (Variable v1, Variable v2) noexcept;

    implementation::ZeroConstanta operator* (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, implementation::Constanta, 
        Parameter, implementation::UnusedParameter> operator* (implementation::Constanta c, Parameter p) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, implementation::Constanta, 
        Variable, implementation::UnusedParameter> operator* (implementation::Constanta c, Variable v) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Parameter p) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, implementation::Constanta, 
        Parameter, implementation::UnusedParameter> operator* (Parameter p, implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator* (Parameter p, implementation::ZeroConstanta c) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, 
        Parameter, Variable, implementation::UnusedParameter> operator* (Parameter p, Variable v) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, implementation::Constanta, 
        Variable, implementation::UnusedParameter> operator* (Variable v, implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator* (Variable v, implementation::ZeroConstanta c) noexcept;

    implementation::Function<implementation::function_name::PRODUCT, 
        Parameter, Variable, implementation::UnusedParameter> operator* (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return product(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return product(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, Parameter p)
    {
        return product(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return product(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return product(v, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return product(v, func);
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator* (const implementation::Function<N1, F1, S1, I1>& func1, 
                   const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return product(func1, func2);
    }

// functions

    template<class T>
    auto exponenta(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::EXPONENTA,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    auto sq_root(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::SQUARE_ROOT,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    // I is exponent, argument (T) is base degree
    template<int I, class T>
    auto power(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::POWER,
            T,
            implementation::UnusedArgument,
            I
        >(argument);
    }

    template<std::uint8_t I, class T>
    auto root(const T& argument)
    {
        if constexpr (I != 2)
            return implementation::create_function<
                implementation::function_name::ROOT,
                T,
                implementation::UnusedArgument,
                I
            >(argument);
        else
            return sq_root(argument);    
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
