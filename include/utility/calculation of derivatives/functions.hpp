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
    using Summ_t = Function<function_name::SUMM, F, S, UnusedParameter>;
    template<class F, class S>
    using Product_t = Function<function_name::PRODUCT, F, S, UnusedParameter>;
    template<class F, class S>
    using Difference_t = Summ_t<F, Product_t<Constanta, S>>;
    template<class F, class S>
    using Ratio_t = Product_t<F, Function<function_name::POWER, S, UnusedArgument, -1>>;

    template<class F, class S>
    auto summ(const F& first, const S& second)
    {
        return const_function_folding(Summ_t<F, S>(first, second));
    }

    template<class F, class S>
    auto product(const F& first, const S& second)
    {
        return const_function_folding(Product_t<F, S>(first, second));
    }
}

// fcd - functions for calculation of derivatives
namespace utils::fcd
{
    implementation::Constanta operator- (implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator- (implementation::ZeroConstanta c) noexcept;

    implementation::Product_t<implementation::Constanta, Parameter> operator- (Parameter p) noexcept;
    
    implementation::Product_t<implementation::Constanta, Variable> operator- (Variable v) noexcept;
    
    template<implementation::function_name N, class F, class S, int I>
    auto operator- (const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(implementation::Constanta(-1), func);
    }

    implementation::Constanta operator+ (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator+ (implementation::ZeroConstanta c1, 
                                             implementation::ZeroConstanta c2) noexcept;

    implementation::Summ_t<Parameter, Parameter> operator+ (Parameter p1, Parameter p2) noexcept;

    implementation::Product_t<implementation::Constanta, Variable> operator+ (Variable v1, Variable v2) noexcept;

    implementation::Constanta operator+ (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Summ_t<implementation::Constanta, Parameter> operator+ (implementation::Constanta c, 
                                                                          Parameter p) noexcept;

    implementation::Summ_t<implementation::Constanta, Variable> operator+ (implementation::Constanta c, 
                                                                         Variable v) noexcept;

    implementation::Constanta operator+ (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    Parameter operator+ (implementation::ZeroConstanta c, Parameter p) noexcept;

    Variable operator+ (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::Summ_t<implementation::Constanta, Parameter> operator+ (Parameter p, 
                                                                            implementation::Constanta c) noexcept;

    Parameter operator+ (Parameter p, implementation::ZeroConstanta c) noexcept;

    implementation::Summ_t<Parameter, Variable> operator+ (Parameter p, Variable v) noexcept;

    implementation::Summ_t<implementation::Constanta, Variable> operator+ (Variable v, 
                                                                           implementation::Constanta c) noexcept;

    Variable operator+ (Variable v, implementation::ZeroConstanta c) noexcept;

    implementation::Summ_t<Parameter, Variable> operator+ (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::summ(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(c, func);
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
        return implementation::summ(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::summ(v, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator+ (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(v, func);
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator+ (const implementation::Function<N1, F1, S1, I1>& func1, 
                    const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::summ(func1, func2);
    }

    implementation::Constanta operator* (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Product_t<Parameter, Parameter> operator* (Parameter p1, Parameter p2) noexcept;

    implementation::Function<implementation::function_name::POWER, 
        Variable, implementation::UnusedArgument, 2> operator* (Variable v1, Variable v2) noexcept;

    implementation::ZeroConstanta operator* (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Product_t<implementation::Constanta, Parameter> operator* (implementation::Constanta c, 
                                                                             Parameter p) noexcept;

    implementation::Product_t<implementation::Constanta, Variable> operator* (implementation::Constanta c, 
                                                                            Variable v) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Parameter p) noexcept;

    implementation::ZeroConstanta operator* (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::Product_t<implementation::Constanta, Parameter> operator* (Parameter p, 
                                                                               implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator* (Parameter p, implementation::ZeroConstanta c) noexcept;

    implementation::Product_t<Parameter, Variable> operator* (Parameter p, Variable v) noexcept;

    implementation::Product_t<implementation::Constanta, Variable> operator* (Variable v, 
                                                                              implementation::Constanta c) noexcept;

    implementation::ZeroConstanta operator* (Variable v, implementation::ZeroConstanta c) noexcept;

    implementation::Product_t<Parameter, Variable> operator* (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::product(c, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(c, func);
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
        return implementation::product(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::product(v, func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator* (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(v, func);
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator* (const implementation::Function<N1, F1, S1, I1>& func1, 
                   const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::product(func1, func2);
    }

    implementation::Constanta operator- (implementation::Constanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator- (implementation::ZeroConstanta c1, 
                                             implementation::ZeroConstanta c2) noexcept;

    implementation::Difference_t<Parameter, Parameter> operator- (Parameter p1, Parameter p2) noexcept;

    implementation::ZeroConstanta operator- (Variable v1, Variable v2) noexcept;

    implementation::Constanta operator- (implementation::Constanta c1, implementation::ZeroConstanta c2) noexcept;

    implementation::Difference_t<implementation::Constanta, Parameter> operator- (implementation::Constanta c, 
                                                                                  Parameter p) noexcept;

    implementation::Difference_t<implementation::Constanta, Variable> operator- (implementation::Constanta c, 
                                                                                 Variable v) noexcept;

    implementation::Constanta operator- (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    implementation::Product_t<implementation::Constanta, Parameter> operator- (implementation::ZeroConstanta c, 
                                                                               Parameter p) noexcept;

    implementation::Product_t<implementation::Constanta, Variable> operator- (implementation::ZeroConstanta c, 
                                                                              Variable v) noexcept;

    implementation::Summ_t<implementation::Constanta, Parameter> operator- (Parameter p, 
                                                                            implementation::Constanta c) noexcept;

    Parameter operator- (Parameter p, implementation::ZeroConstanta c) noexcept;

    implementation::Difference_t<Parameter, Variable> operator- (Parameter p, Variable v) noexcept;

    implementation::Summ_t<implementation::Constanta, Variable> operator- (Variable v, 
                                                                           implementation::Constanta c) noexcept;

    Variable operator- (Variable v, implementation::ZeroConstanta c) noexcept;

    implementation::Difference_t<Variable, Parameter> operator- (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::summ(implementation::Constanta(-c(0)), func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(c, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (const implementation::Function<N, F, S, I>& func, implementation::ZeroConstanta c)
    {
        return func;
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(implementation::Constanta(-1), func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (const implementation::Function<N, F, S, I>& func, Parameter p)
    {
        return implementation::summ(implementation::product(implementation::Constanta(-1), p), func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(p, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::summ(implementation::product(implementation::Constanta(-1), v), func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator- (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::summ(v, implementation::product(implementation::Constanta(-1), func));
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator- (const implementation::Function<N1, F1, S1, I1>& func1, 
                    const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::summ(func1, implementation::product(implementation::Constanta(-1), func2));
    }

    implementation::Constanta operator/ (implementation::Constanta c1, implementation::Constanta c2);

    implementation::Ratio_t<Parameter, Parameter> operator/ (Parameter p1, Parameter p2) noexcept;

    implementation::Constanta operator/ (Variable v1, Variable v2) noexcept;

     implementation::Ratio_t<implementation::Constanta, Parameter> operator/ (implementation::Constanta c, 
                                                                              Parameter p) noexcept;

    implementation::Ratio_t<implementation::Constanta, Variable> operator/ (implementation::Constanta c, 
                                                                            Variable v) noexcept;

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c1, implementation::Constanta c2) noexcept;

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c, Parameter p) noexcept;

    implementation::ZeroConstanta operator/ (implementation::ZeroConstanta c, Variable v) noexcept;

    implementation::Product_t<implementation::Constanta, Parameter> operator/ (Parameter p, 
                                                                               implementation::Constanta c);

    implementation::Ratio_t<Parameter, Variable> operator/ (Parameter p, Variable v) noexcept;

    implementation::Product_t<implementation::Constanta, Variable> operator/ (Variable v, 
                                                                              implementation::Constanta c);

    implementation::Ratio_t<Variable, Parameter> operator/ (Variable v, Parameter p) noexcept;

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (const implementation::Function<N, F, S, I>& func, implementation::Constanta c)
    {
        return implementation::product(implementation::Constanta(1/c(0)), func);
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (implementation::Constanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(c, implementation::Function<
            implementation::function_name::POWER, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (implementation::ZeroConstanta c, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::ZeroConstanta();
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (const implementation::Function<N, F, S, I>& func, Parameter p)
    {
        return implementation::product(func, implementation::Function<
            implementation::function_name::POWER, Parameter, implementation::UnusedArgument, -1
        >(p));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (Parameter p, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(p, implementation::Function<
            implementation::function_name::POWER, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (const implementation::Function<N, F, S, I>& func, Variable v)
    {
        return implementation::product(func, implementation::Function<
            implementation::function_name::POWER, Variable, implementation::UnusedArgument, -1
        >(v));
    }

    template<implementation::function_name N, class F, class S, int I>
    auto operator/ (Variable v, const implementation::Function<N, F, S, I>& func)
    {
        return implementation::product(v, implementation::Function<
            implementation::function_name::POWER, std::decay_t<decltype(func)>, implementation::UnusedArgument, -1
        >(func));
    }

    template<implementation::function_name N1, class F1, class S1, int I1, 
             implementation::function_name N2, class F2, class S2, int I2>
    auto operator/ (const implementation::Function<N1, F1, S1, I1>& func1, 
                   const implementation::Function<N2, F2, S2, I2>& func2)
    {
        return implementation::product(func1, implementation::Function<
            implementation::function_name::POWER, std::decay_t<decltype(func2)>, implementation::UnusedArgument, -1
        >(func2));
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
            implementation::function_name::ROOT,
            T,
            implementation::UnusedArgument,
            2
        >(argument);
    }

    template<class T>
    auto cb_root(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::ROOT,
            T,
            implementation::UnusedArgument,
            3
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
        return implementation::create_function<
            implementation::function_name::ROOT,
            T,
            implementation::UnusedArgument,
            I
        >(argument);   
    }

    template<class T>
    auto sinus(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::SINUS,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    auto cosinus(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::COSINUS,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<class T>
    auto tangent(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::TANGENT,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    // natural logarithm
    template<class T>
    auto logarithm(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::LOGARITHM_NATURAL,
            T,
            implementation::UnusedArgument,
            implementation::UnusedParameter
        >(argument);
    }

    template<std::uint8_t I, class T>
    auto logarithm(const T& argument)
    {
        static_assert(I > 1, "base of logarithm must be great than 1");
        return product(implementation::Constanta(1/log(I)), logarithm(argument));
    }

    template<std::uint8_t I, class T>
    auto exponential(const T& argument)
    {
        return implementation::create_function<
            implementation::function_name::EXPONENTIAL,
            T,
            implementation::UnusedArgument,
            I
        >(argument);
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_FUNCTION_T
