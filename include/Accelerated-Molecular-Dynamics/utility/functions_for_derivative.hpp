#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include <cmath>
#include <cstdint>
#include <vector>

class Const
{
    const double value;
public:
    Const(const double v) noexcept;

    double compute_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
    Const set_parameters(const std::vector<double>& params) const;
};

class Variable
{
public:
    Variable() noexcept = default;

    double compute_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
    Variable set_parameters(const std::vector<double>& params) const;
};

class Parameter
{
    const uint8_t index;
public:
    Parameter(const uint8_t index) noexcept;

    double compute_value(const double x) const;
    double compute_derivative(const double x) const noexcept;
    Const set_parameters(const std::vector<double>& params) const;
};

namespace
{
    template<template <class> class T>
    Const f_const(const Const c) noexcept 
    { 
        return Const(T<Const>(c).compute_value(0)); 
    }

    template<template <class, class> class F>
    Const f_const(const Const c1, const Const c2) noexcept 
    { 
        return Const(F<Const, Const>(c1, c2).compute_value(0)); 
    }

    template<template <class> class Func, class T>
    auto const_folding(const T argument)
    {
        if constexpr (std::is_same<T, Const>::value)
            return f_const<Func>(argument);
        else
            return Func<T>(argument);
    }

    template<template <class, class> class Func, class First, class Second>
    auto const_folding(const First first_f, const Second second_f)
    {
        if constexpr (std::is_same<First, Const>::value && 
                      std::is_same<Second, Const>::value)
            return f_const<Func>(first_f, second_f);
        else
            return Func<First, Second>(first_f, second_f);
    }

    template<class F, class S>
    class ABinaryFunction
    {
    protected:
        const F inner_function_first;
        const S inner_function_second;

        ABinaryFunction(const F func1, const S func2) noexcept;
    public:
        virtual double compute_value(const double x) const = 0;
        virtual double compute_derivative(const double x) const = 0;
    };

    template<class F, class S>
    class Sum: public ABinaryFunction<F, S>
    {
    public:
        Sum(const F first, const S second) noexcept;
        double compute_value(const double x) const override;
        double compute_derivative(const double x) const override;

        auto set_parameters(const std::vector<double>& params) const
        {
            auto first_f = ABinaryFunction<F, S>::inner_function_first.set_parameters(params);                
            auto second_f = ABinaryFunction<F, S>::inner_function_second.set_parameters(params);
            return const_folding<Sum, decltype(first_f), decltype(second_f)>(first_f, second_f);            
        }
    };

    template<class F, class S>
    class Product: public ABinaryFunction<F, S>
    {
    public:
        Product(const F first, const S second) noexcept;
        double compute_value(const double x) const override;
        double compute_derivative(const double x) const override;

        auto set_parameters(const std::vector<double>& params) const
        {
            auto first_f = ABinaryFunction<F, S>::inner_function_first.set_parameters(params);                
            auto second_f = ABinaryFunction<F, S>::inner_function_second.set_parameters(params);
            return const_folding<Product, decltype(first_f), decltype(second_f)>(first_f, second_f);            
        }
    };

    template<class T>
    class AUnaryFunction
    {
    protected:
        const T inner_function;

        AUnaryFunction(const T func) noexcept;
        virtual double self_value(const double x) const = 0;
        virtual double self_derivative(const double x) const = 0;
    public:
        double compute_value(const double x) const;
        double compute_derivative(const double x) const;
    };

    template<class T>
    class Exp: public AUnaryFunction<T>
    {
    protected:
        double self_value(const double x) const override;
        double self_derivative(const double x) const override;
    public:
        Exp(const T v) noexcept;

        auto set_parameters(const std::vector<double>& params) const
        {
            auto func = AUnaryFunction<T>::inner_function.set_parameters(params);
            return const_folding<Exp, decltype(func)>(func);            
        }
    };

    template<class T>
    class Pow: public AUnaryFunction<T>
    {
        const float p;
    protected:
        double self_value(const double x) const override;
        double self_derivative(const double x) const override;
    public:
        Pow(const T v, const float power) noexcept;

        auto set_parameters(const std::vector<double>& params) const
        {
            auto func = AUnaryFunction<T>::inner_function.set_parameters(params);
            if constexpr (std::is_same<decltype(func), Const>::value)
                return Const(Pow<Const>(func, p).compute_value(0));
            else
                return Pow<decltype(func)>(func, p);            
        }
    };

}

template<class F, class S>
auto f_sum(const F first, const S second) noexcept 
{ 
    return const_folding<Sum, decltype(first), decltype(second)>(first, second);
}

template<class F, class S>
auto f_product(const F first, const S second) noexcept 
{
    return const_folding<Product, decltype(first), decltype(second)>(first, second);
}

template<class T>
auto f_exp(const T v) noexcept 
{ 
    return const_folding<Exp, decltype(v)>(v);
}

template<class T>
auto f_pow(const T v, const float p) noexcept 
{
    if constexpr (std::is_same<T, Const>::value)
        return f_const<Pow>(v);
    else
        return Pow<decltype(v)>(v, p); 
}

template<class T>
double compute_value(const T function, const double argument)
{
    return function.compute_value(argument);
}

template<class T>
double compute_derivative(const T function, const double argument)
{
    return function.compute_derivative(argument);
}

template<class F, class S>
ABinaryFunction<F, S>::ABinaryFunction(const F func1, const S func2) noexcept
    : inner_function_first{ func1 }, inner_function_second{ func2 }
{
}

template<class F, class S>
Sum<F, S>::Sum(const F first, const S second) noexcept
    : ABinaryFunction<F, S>{ first, second }
{
}

template<class F, class S>
double Sum<F, S>::compute_value(const double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_value(x) + 
           ABinaryFunction<F, S>::inner_function_second.compute_value(x); 
}

template<class F, class S>
double Sum<F, S>::compute_derivative(const double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_derivative(x) + 
           ABinaryFunction<F, S>::inner_function_second.compute_derivative(x); 
}

template<class F, class S>
Product<F, S>::Product(const F first, const S second) noexcept
    : ABinaryFunction<F, S>{ first, second }
{
}

template<class F, class S>
double Product<F, S>::compute_value(const double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_value(x) * 
           ABinaryFunction<F, S>::inner_function_second.compute_value(x); 
}

template<class F, class S>
double Product<F, S>::compute_derivative(const double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_derivative(x)*
           ABinaryFunction<F, S>::inner_function_second.compute_value(x)  +
           ABinaryFunction<F, S>::inner_function_first.compute_value(x)*
           ABinaryFunction<F, S>::inner_function_second.compute_derivative(x); 
}

template<class T>
AUnaryFunction<T>::AUnaryFunction(const T func) noexcept
    : inner_function{ func }
{
}

template<class T>
double AUnaryFunction<T>::compute_value(const double x) const
{ 
    return self_value(inner_function.compute_value(x)); 
}

template<class T>
double AUnaryFunction<T>::compute_derivative(const double x) const
{
    return self_derivative(inner_function.compute_value(x)) * inner_function.compute_derivative(x);
}

template<class T>
Exp<T>::Exp(const T v) noexcept
    : AUnaryFunction<T>{ v }
{
}

template<class T>
double Exp<T>::self_value(const double x) const 
{ 
    return exp(x); 
}

template<class T>
double Exp<T>::self_derivative(const double x) const 
{ 
    return exp(x); 
}

template<class T>
Pow<T>::Pow(const T v, const float power) noexcept 
    : AUnaryFunction<T>{ v }, p{ power }
{
}

template<class T>
double Pow<T>::self_value(const double x) const 
{ 
    return pow(x, p); 
}

template<class T>
double Pow<T>::self_derivative(const double x) const 
{ 
    return p * pow(x, p-1); 
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_H
