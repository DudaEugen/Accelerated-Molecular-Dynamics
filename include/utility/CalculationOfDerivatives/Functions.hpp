#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T

#include "helper/SetParameters.hpp"
#include "helper/DerivativeRules.hpp"

namespace utils::fcd::implementation
{
    template<FunctionName N, class T, class S, int I>
    constexpr auto createFunction(const T& argument)
    {
        if constexpr (std::is_same_v<T, double> || std::is_same_v<T, int>)
            return implementation::constFunctionFolding(implementation::Function<
                N, Constanta, S, I
            >(implementation::Constanta{argument}));
        else if constexpr (std::is_same_v<T, Constanta>)
            return implementation::constFunctionFolding(implementation::Function<
                N, Constanta, S, I
            >(argument));
        else
            return implementation::constFunctionFolding(implementation::Function<
                N, T, S, I
            >(argument));
    }

    template<class F, class S>
    using Summ_t = Function<FunctionName::Summ, F, S, UnusedParameter>;
    template<class F, class S>
    using Product_t = Function<FunctionName::Product, F, S, UnusedParameter>;
    template<class F, class S>
    using Difference_t = Summ_t<F, Product_t<Constanta, S>>;
    template<class F, class S>
    using Ratio_t = Product_t<F, Function<FunctionName::Power, S, UnusedArgument, -1>>;

    template<class F, class S>
    constexpr auto summ(const F& first, const S& second)
    {
        return constFunctionFolding(Summ_t<F, S>(first, second));
    }

    template<class F, class S>
    constexpr auto product(const F& first, const S& second)
    {
        return constFunctionFolding(Product_t<F, S>(first, second));
    }
}

// fcd - functions for CalculationOfDerivatives
namespace utils::fcd
{
    // functions

    template<class T>
    constexpr auto exponenta(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Exponenta,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    constexpr auto sqRoot(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Root,
            T,
            implementation::UnusedArgument,
            2
        >(argument);
    }

    template<class T>
    constexpr auto cbRoot(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Root,
            T,
            implementation::UnusedArgument,
            3
        >(argument);
    }

    // I is exponent, argument (T) is base degree
    template<int I, class T>
    constexpr auto power(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Power,
            T,
            implementation::UnusedArgument,
            I
        >(argument);
    }

    template<std::uint8_t I, class T>
    constexpr auto root(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Root,
            T,
            implementation::UnusedArgument,
            I
        >(argument);   
    }

    template<class T>
    constexpr auto sinus(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Sinus,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    constexpr auto cosinus(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Cosinus,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    constexpr auto tangent(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Tangent,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    // natural logarithm
    template<class T>
    constexpr auto logarithm(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::LogarithmNatural,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    constexpr auto heavisideStep(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::HeavisideStep,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<std::uint8_t I, class T>
    constexpr auto logarithm(const T& argument)
    {
        static_assert(I > 1, "base of logarithm must be great than 1");
        return product(implementation::Constanta(1/log(I)), logarithm(argument));
    }

    template<std::uint8_t I, class T>
    constexpr auto exponential(const T& argument)
    {
        return implementation::createFunction<
            implementation::FunctionName::Exponential,
            T,
            implementation::UnusedArgument,
            I
        >(argument);
    }

    template<class T>
    constexpr auto dynamicSumm(const T& argument)
    {
        return implementation::Function<
            implementation::FunctionName::DynamicSumm,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }
}

// fcd - functions for CalculationOfDerivatives
namespace utils::fcd
{
//operators

    implementation::Constanta operator- (implementation::Constanta c) noexcept;

    constexpr implementation::ZeroConstanta operator- (implementation::ZeroConstanta c) noexcept
    {
        return implementation::ZeroConstanta();
    }

    template<std::uint8_t I>
    constexpr auto operator- (Parameter<I> p) noexcept
    {
        return implementation::product(implementation::Constanta(-1), p);
    }
    
    implementation::Product_t<implementation::Constanta, Variable> operator- (Variable v) noexcept;

    implementation::Product_t<implementation::Constanta, DynamicParameter> operator- (DynamicParameter v) noexcept;
    
    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(implementation::Constanta(-1), func);
    }

    implementation::Constanta operator+ (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    constexpr auto operator+ (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept
    {
        return implementation::ZeroConstanta();
    }

    template<std::uint8_t I1, std::uint8_t I2>
    constexpr auto operator+ (Parameter<I1> p1, Parameter<I2> p2) noexcept
    {
        return implementation::summ(p1, p2);
    }

    implementation::Product_t<implementation::Constanta, Variable> operator+ (Variable v1, Variable v2) noexcept;

    implementation::Product_t<implementation::Constanta, DynamicParameter> operator+ (DynamicParameter v1, 
                                                                                      DynamicParameter v2) noexcept;

    implementation::Constanta operator+ (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    template<std::uint8_t I>
    constexpr auto operator+ (implementation::Constanta c, Parameter<I> p) noexcept
    {
        return implementation::summ(c, p);
    }

    implementation::Summ_t<implementation::Constanta, Variable> operator+ (implementation::Constanta c, 
                                                                         Variable v) noexcept;
    
    implementation::Summ_t<implementation::Constanta, DynamicParameter> operator+ (implementation::Constanta c, 
                                                                                   DynamicParameter v) noexcept;

    implementation::Constanta operator+ (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    template<std::uint8_t I>
    constexpr Parameter<I> operator+ (implementation::ZeroConstanta c, Parameter<I> p) noexcept
    {
        return p;
    }

    Variable operator+ (implementation::ZeroConstanta c, Variable v) noexcept;

    DynamicParameter operator+ (implementation::ZeroConstanta c, DynamicParameter v) noexcept;

    template<std::uint8_t I>
    constexpr auto operator+ (Parameter<I> p, implementation::Constanta c) noexcept
    {
        return implementation::summ(c, p);
    }

    template<std::uint8_t I>
    constexpr Parameter<I> operator+ (Parameter<I> p, implementation::ZeroConstanta c) noexcept
    {
        return p;
    }

    template<std::uint8_t I>
    constexpr auto operator+ (Parameter<I> p, Variable v) noexcept
    {
        return implementation::summ(p, v);
    }

    template<std::uint8_t I>
    constexpr auto operator+ (Parameter<I> p, DynamicParameter v) noexcept
    {
        return implementation::summ(p, v);
    }

    implementation::Summ_t<implementation::Constanta, Variable> operator+ (Variable v, 
                                                                           implementation::Constanta c) noexcept;

    Variable operator+ (Variable v, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    constexpr auto operator+ (Variable v, Parameter<I> p) noexcept
    {
        return implementation::summ(p, v);
    }

    implementation::Summ_t<DynamicParameter, Variable> operator+ (Variable v, DynamicParameter c) noexcept;

    implementation::Summ_t<implementation::Constanta, DynamicParameter> operator+ (DynamicParameter p, 
                                                                  implementation::Constanta c) noexcept;
    
    DynamicParameter operator+ (DynamicParameter p, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    constexpr implementation::Summ_t<Parameter<I>, DynamicParameter> operator+ (DynamicParameter dp, 
                                                                                Parameter<I> p) noexcept
    {
        return implementation::summ(p, dp);
    }

    implementation::Summ_t<DynamicParameter, Variable> operator+ (DynamicParameter p, Variable v) noexcept;

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::summ(c, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(c, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return func;
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return func;
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator+ (const implementation::Function<N, F, S, I>& func, Parameter<IPar> p)
    {
        return implementation::summ(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator+ (Parameter<IPar> p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::summ(v, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(v, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (const implementation::Function<N, F, S, I>& func, DynamicParameter p)
    {
        return implementation::summ(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator+ (DynamicParameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, func);
    }

    template<implementation::FunctionName N1, class F1, class S1, int I1, 
             implementation::FunctionName N2, class F2, class S2, int I2>
    constexpr auto operator+ (const implementation::Function<N1, F1, S1, I1>& func1, 
                              const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::summ(func1, func2);
    }

    implementation::Constanta operator* (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    constexpr auto operator* (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept
    {
        return implementation::ZeroConstanta();
    }

    template<std::uint8_t I1, std::uint8_t I2>
    constexpr auto operator* (Parameter<I1> p1, Parameter<I2> p2) noexcept
    {
        return implementation::product(p1, p2);
    }

    implementation::Function<implementation::FunctionName::Power, 
        Variable, implementation::UnusedArgument, 2> operator* (Variable v1, Variable v2) noexcept;
    
    implementation::Function<implementation::FunctionName::Power, 
        DynamicParameter, implementation::UnusedArgument, 2> operator* (DynamicParameter p1, DynamicParameter p2) noexcept;

    implementation::ZeroConstanta operator* (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    template<std::uint8_t I>
    constexpr auto operator* (implementation::Constanta c, Parameter<I> p) noexcept
    {
        return implementation::product(c, p);
    }
                                                                             
    implementation::Product_t<implementation::Constanta, Variable> operator* (implementation::Constanta c, 
                                                                            Variable v) noexcept;
    
    implementation::Product_t<implementation::Constanta, DynamicParameter> operator* (implementation::Constanta c, 
                                                                            DynamicParameter p) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    template<std::uint8_t I>
    constexpr implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Parameter<I> p) noexcept
    {
        return implementation::ZeroConstanta();
    }

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, DynamicParameter v) noexcept;

    template<std::uint8_t I>
    constexpr auto operator* (Parameter<I> p, implementation::Constanta c) noexcept
    {
        return implementation::product(c, p);
    }

    template<std::uint8_t I>
    constexpr implementation::ZeroConstanta operator* (Parameter<I> p, implementation::ZeroConstanta c) noexcept
    {
        return implementation::ZeroConstanta();
    }

    template<std::uint8_t I>
    constexpr auto operator* (Parameter<I> p, Variable v) noexcept
    {
        return implementation::product(p, v);
    }

    template<std::uint8_t I>
    constexpr auto operator* (Parameter<I> p, DynamicParameter dp) noexcept
    {
        return implementation::product(p, dp);
    }

    implementation::Product_t<implementation::Constanta, Variable> operator* (Variable v, 
                                                                              implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator* (Variable v, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    constexpr auto operator* (Variable v, Parameter<I> p) noexcept
    {
        return implementation::product(p, v);
    }

    implementation::Product_t<DynamicParameter, Variable> operator* (Variable v, DynamicParameter p) noexcept;

    implementation::Product_t<implementation::Constanta, DynamicParameter> operator* (DynamicParameter p, 
                                                                    implementation::Constanta c) noexcept;
    
    implementation::ZeroConstanta operator* (DynamicParameter p, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    implementation::Product_t<Parameter<I>, DynamicParameter> operator* (DynamicParameter dp, 
                                                                         Parameter<I> p) noexcept
    {
        return implementation::product(p, dp);
    }
    
    implementation::Product_t<DynamicParameter, Variable> operator* (DynamicParameter p, Variable v) noexcept;

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::product(c, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(c, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator* (const implementation::Function<N, F, S, I>& func, Parameter<IPar> p)
    {
        return implementation::product(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator* (Parameter<IPar> p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::product(v, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(v, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (const implementation::Function<N, F, S, I>& func, DynamicParameter p)
    {
        return implementation::product(p, func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator* (DynamicParameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, func);
    }

    template<implementation::FunctionName N1, class F1, class S1, int I1, 
             implementation::FunctionName N2, class F2, class S2, int I2>
    constexpr auto operator* (const implementation::Function<N1, F1, S1, I1>& func1, 
                              const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::product(func1, func2);
    }

    implementation::Constanta operator- (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    constexpr auto operator- (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept
    {
        return implementation::ZeroConstanta();
    }

    template<std::uint8_t I1, std::uint8_t I2>
    constexpr auto operator- (Parameter<I1> p1, Parameter<I2> p2) noexcept
    {
        return p1 + (-p2);
    }

    implementation::ZeroConstanta operator- (Variable v1, Variable v2) noexcept;

    implementation::ZeroConstanta operator- (DynamicParameter v1, DynamicParameter v2) noexcept;

    implementation::Constanta operator- (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    template<std::uint8_t I>
    constexpr auto operator- (implementation::Constanta c, Parameter<I> p) noexcept
    {
        return c + (-p);
    }

    implementation::Difference_t<implementation::Constanta, Variable> operator- (implementation::Constanta c, 
                                                                                 Variable v) noexcept;
    
    implementation::Difference_t<implementation::Constanta, DynamicParameter> 
        operator- (implementation::Constanta c, DynamicParameter p) noexcept;

    implementation::Constanta operator- (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    template<std::uint8_t I>
    constexpr auto operator- (implementation::ZeroConstanta c, Parameter<I> p) noexcept
    {
        return -p;
    }

    implementation::Product_t<implementation::Constanta, Variable> operator- (implementation::ZeroConstanta c, 
                                                                              Variable v) noexcept;
    
    implementation::Product_t<implementation::Constanta, DynamicParameter> 
        operator- (implementation::ZeroConstanta c, DynamicParameter p) noexcept;

    template<std::uint8_t I>
    constexpr auto operator- (Parameter<I> p, implementation::Constanta c) noexcept
    {
        return p + implementation::Constanta(-c(0));
    }

    template<std::uint8_t I>
    constexpr Parameter<I> operator- (Parameter<I> p, implementation::ZeroConstanta c) noexcept
    {
        return p;
    }

    template<std::uint8_t I>
    constexpr auto operator- (Parameter<I> p, Variable v) noexcept
    {
        return p + (-v);
    }

    template<std::uint8_t I>
    constexpr auto operator- (Parameter<I> p, DynamicParameter dp) noexcept
    {
        return p + (-dp);
    }

    implementation::Summ_t<implementation::Constanta, Variable> operator- (Variable v, 
                                                                           implementation::Constanta c) noexcept;

    Variable operator- (Variable v, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    constexpr auto operator- (Variable v, Parameter<I> p) noexcept
    {
        return v + (-p);
    }

    implementation::Summ_t<DynamicParameter, implementation::Product_t<implementation::Constanta, Variable>> 
        operator- (Variable v, DynamicParameter c) noexcept;
    
    implementation::Summ_t<implementation::Constanta, DynamicParameter> operator- (DynamicParameter p, 
                                                                        implementation::Constanta c) noexcept;

    DynamicParameter operator- (DynamicParameter p, implementation::ZeroConstanta c) noexcept;

    template<std::uint8_t I>
    constexpr auto operator- (DynamicParameter dp, Parameter<I> p) noexcept
    {
        return p + (-dp);
    }

    implementation::Difference_t<DynamicParameter, Variable> operator- (DynamicParameter p, 
                                                                        Variable v) noexcept;

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::summ(implementation::Constanta(-c(0)), func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(c, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return func;
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(implementation::Constanta(-1), func);
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func, Parameter<IPar> p)
    {
        return implementation::summ(implementation::product(implementation::Constanta(-1), p), func);
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator- (Parameter<IPar> p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::summ(implementation::product(implementation::Constanta(-1), v), func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(v, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (const implementation::Function<N, F, S, I>& func, DynamicParameter p)
    {
        return implementation::summ(implementation::product(implementation::Constanta(-1), p), func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator- (DynamicParameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::FunctionName N1, class F1, class S1, int I1, 
             implementation::FunctionName N2, class F2, class S2, int I2>
    constexpr auto operator- (const implementation::Function<N1, F1, S1, I1>& func1, 
                              const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::summ(func1, implementation::product(implementation::Constanta(-1), func2));
    }

    implementation::Constanta operator/ (implementation::Constanta c1, implementation::Constanta c2);

    template<std::uint8_t I1, std::uint8_t I2>
    constexpr auto operator/ (Parameter<I1> p1, Parameter<I2> p2) noexcept
    {
        return p1 * power<-1>(p2);
    }

    implementation::Constanta operator/ (Variable v1, Variable v2) noexcept;

    implementation::Constanta operator/ (DynamicParameter v1, DynamicParameter v2) noexcept;

    template<std::uint8_t I>
    constexpr auto operator/ (implementation::Constanta c, Parameter<I> p) noexcept
    {
        return c * power<-1>(p);
    }

    implementation::Ratio_t<implementation::Constanta, Variable> operator/ (implementation::Constanta c, 
                                                                            Variable v) noexcept;
    
    implementation::Ratio_t<implementation::Constanta, DynamicParameter> operator/ (implementation::Constanta c, 
                                                                                    DynamicParameter v) noexcept;

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    template<std::uint8_t I>
    constexpr implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c, Parameter<I> p) noexcept
    {
        return implementation::ZeroConstanta();
    }

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c, DynamicParameter p) noexcept;

    template<std::uint8_t I>
    constexpr auto operator/ (Parameter<I> p, implementation::Constanta c)
    {
        return implementation::Constanta(1/c(0)) * p;
    }

    template<std::uint8_t I>
    constexpr auto operator/ (Parameter<I> p, Variable v) noexcept
    {
        return p * power<-1>(v);
    }

    template<std::uint8_t I>
    constexpr auto operator/ (Parameter<I> p, DynamicParameter dp) noexcept
    {
        return p * power<-1>(dp);
    }

    implementation::Product_t<implementation::Constanta, Variable> operator/ (Variable v, 
                                                                              implementation::Constanta c);

    template<std::uint8_t I>
    constexpr auto operator/ (Variable v, Parameter<I> p) noexcept
    {
        return v * power<-1>(p);
    }

    implementation::Ratio_t<Variable, DynamicParameter> operator/ (Variable v, DynamicParameter p) noexcept;

    implementation::Product_t<implementation::Constanta, DynamicParameter> operator/ (DynamicParameter p, 
                                                                            implementation::Constanta c);
    
    template<std::uint8_t I>
    constexpr auto operator/ (DynamicParameter dp, Parameter<I> p) noexcept
    {
        return dp * power<-1>(p);
    }

    implementation::Ratio_t<DynamicParameter, Variable> operator/ (DynamicParameter p, Variable v) noexcept;

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::product(implementation::Constanta(1/c(0)), func);
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(c, implementation::Function<
            implementation::FunctionName::Power, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator/ (const implementation::Function<N, F, S, I>& func, Parameter<IPar> p)
    {
        return implementation::product(func, implementation::Function<
            implementation::FunctionName::Power, Parameter<IPar>, implementation::UnusedArgument, -1
        >(p));
    }

    template<implementation::FunctionName N, class F, class S, int I, std::uint8_t IPar>
    constexpr auto operator/ (Parameter<IPar> p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, implementation::Function<
            implementation::FunctionName::Power, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::product(func, implementation::Function<
            implementation::FunctionName::Power, Variable, implementation::UnusedArgument, -1
        >(v));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(v, implementation::Function<
            implementation::FunctionName::Power, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (const implementation::Function<N, F, S, I>& func, DynamicParameter p)
    {
        return implementation::product(func, implementation::Function<
            implementation::FunctionName::Power, Variable, implementation::UnusedArgument, -1
        >(p));
    }

    template<implementation::FunctionName N, class F, class S, int I>
    constexpr auto operator/ (DynamicParameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, implementation::Function<
            implementation::FunctionName::Power, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::FunctionName N1, class F1, class S1, int I1, 
             implementation::FunctionName N2, class F2, class S2, int I2>
    constexpr auto operator/ (const implementation::Function<N1, F1, S1, I1>& func1, 
                              const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::product(func1, implementation::Function<
            implementation::FunctionName::Power, std::decay_t<decltype(func2)>, implementation::UnusedArgument, -1
        >(func2));
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
