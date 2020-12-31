#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include <cmath>
#include <cstdint>
#include <vector>
#include <exception>

template<class T>
class Const;

Const(int) -> Const<double>;

template<class T>
class Variable;

template<class T>
class Parameter;

template<>
class Const<double>
{
    const double value;
public:
    Const(double v) noexcept
        : value{ v }
    {
    }

    static constexpr bool is_const = true;
    
    const double compute_value(double x) const noexcept { return value; }
    const double compute_derivative(double x) const noexcept { return 0; }

    template<class P>
    const Const& set_parameters(const std::vector<P>& params) const { return *this; };
};

template<>
class Variable<double>
{
public:
    Variable() noexcept = default;

    static constexpr bool is_const = false;

    const double compute_value(const double x) const noexcept { return x; }
    const double compute_derivative(const double x) const noexcept { return 1; }

    template<class P>
    const Variable& set_parameters(const std::vector<P>& params) const
    {
        return *this;
    }
};

template<>
class Parameter<double>
{
    const uint8_t index;
public:
    Parameter(uint8_t i) noexcept
        : index{ i }
    {
    }

    static constexpr bool is_const = false;

    const double compute_value(double x) const
    {
        throw std::runtime_error("class Parameter can't compute value");
    }
    const double compute_derivative(double x) const noexcept { return 0; }

    template<class P>
    Const<P> set_parameters(const std::vector<P>& params) const 
    {
        return Const(params[index]);
    }
};

namespace
{
    template<template <class> class T, class A>
    auto f_const(const A& arg) noexcept 
    { 
        return Const(T<A>(arg).compute_value(0)); 
    }

    template<template <class, class> class F, class A>
    auto f_const(const A& arg1, const A& arg2) noexcept 
    { 
        return Const(F<A, A>(arg1, arg2).compute_value(0)); 
    }

    template<template <class> class Func, class T>
    auto const_folding(const T& argument)
    {
        if constexpr (T::is_const)
            return f_const<Func>(argument);
        else
            return Func<T>(argument);
    }

    template<template <class, class> class Func, class First, class Second>
    auto const_folding(const First& first_f, const Second& second_f)
    {
        if constexpr (First::is_const && Second::is_const)
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

        ABinaryFunction(const F& func1, const S& func2) noexcept;
    public:
        static constexpr bool is_const = false;

        virtual double compute_value(const double x) const = 0;
        virtual double compute_derivative(const double x) const = 0;
    };

    template<class F, class S>
    class Sum: public ABinaryFunction<F, S>
    {
    public:
        Sum(const F& first, const S& second) noexcept;
        double compute_value(double x) const override;
        double compute_derivative(double x) const override;

        template<class P>
        auto set_parameters(const std::vector<P>& params) const
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
        Product(const F& first, const S& second) noexcept;
        double compute_value(double x) const override;
        double compute_derivative(double x) const override;

        template<class P>
        auto set_parameters(const std::vector<P>& params) const
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

        AUnaryFunction(const T& func) noexcept;
        virtual double self_value(double x) const = 0;
        virtual double self_derivative(double x) const = 0;
    public:
        static constexpr bool is_const = false;

        double compute_value(const double x) const;
        double compute_derivative(const double x) const;
    };

    template<class T>
    class Exp: public AUnaryFunction<T>
    {
    protected:
        double self_value(double x) const override;
        double self_derivative(double x) const override;
    public:
        Exp(const T& v) noexcept;

        template<class P>
        auto set_parameters(const std::vector<P>& params) const
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
        double self_value(double x) const override;
        double self_derivative(double x) const override;
    public:
        Pow(const T& v, float power) noexcept;

        template<class P>
        auto set_parameters(const std::vector<P>& params) const
        {
            auto func = AUnaryFunction<T>::inner_function.set_parameters(params);
            if constexpr (decltype(func)::is_const)
                return Const(Pow<decltype(func)>(func, p).compute_value(0));
            else
                return Pow<decltype(func)>(func, p);            
        }
    };

}

auto f_var()
{
    return Variable<double>();
}

auto f_param(const uint8_t index) { return Parameter<double>(index); }

template<class F, class S>
auto f_sum(const F& first, const S& second) noexcept 
{ 
    return const_folding<Sum, F, S>(first, second);
}

template<class F, class S>
auto f_product(const F& first, const S& second) noexcept 
{
    return const_folding<Product, F, S>(first, second);
}

template<class T>
auto f_exp(const T& v) noexcept 
{ 
    return const_folding<Exp, T>(v);
}

template<class T>
auto f_pow(const T& v, const float p) noexcept 
{
    if constexpr (T::is_const)
        return Const(Pow<T>(v, p).compute_value(0));
    else
        return Pow<T>(v, p); 
}

// definitions of methods

template<class F, class S>
ABinaryFunction<F, S>::ABinaryFunction(const F& func1, const S& func2) noexcept
    : inner_function_first{ func1 }, inner_function_second{ func2 }
{
}

template<class F, class S>
Sum<F, S>::Sum(const F& first, const S& second) noexcept
    : ABinaryFunction<F, S>{ first, second }
{
}

template<class F, class S>
double Sum<F, S>::compute_value(double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_value(x) + 
           ABinaryFunction<F, S>::inner_function_second.compute_value(x); 
}

template<class F, class S>
double Sum<F, S>::compute_derivative(double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_derivative(x) + 
           ABinaryFunction<F, S>::inner_function_second.compute_derivative(x); 
}

template<class F, class S>
Product<F, S>::Product(const F& first, const S& second) noexcept
    : ABinaryFunction<F, S>{ first, second }
{
}

template<class F, class S>
double Product<F, S>::compute_value(double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_value(x) * 
           ABinaryFunction<F, S>::inner_function_second.compute_value(x); 
}

template<class F, class S>
double Product<F, S>::compute_derivative(double x) const
{ 
    return ABinaryFunction<F, S>::inner_function_first.compute_derivative(x)*
           ABinaryFunction<F, S>::inner_function_second.compute_value(x)  +
           ABinaryFunction<F, S>::inner_function_first.compute_value(x)*
           ABinaryFunction<F, S>::inner_function_second.compute_derivative(x); 
}

template<class T>
AUnaryFunction<T>::AUnaryFunction(const T& func) noexcept
    : inner_function{ func }
{
}

template<class T>
double AUnaryFunction<T>::compute_value(double x) const
{ 
    return self_value(inner_function.compute_value(x)); 
}

template<class T>
double AUnaryFunction<T>::compute_derivative(double x) const
{
    return self_derivative(inner_function.compute_value(x)) * inner_function.compute_derivative(x);
}

template<class T>
Exp<T>::Exp(const T& v) noexcept
    : AUnaryFunction<T>{ v }
{
}

template<class T>
double Exp<T>::self_value(double x) const 
{ 
    return exp(x); 
}

template<class T>
double Exp<T>::self_derivative(double x) const 
{ 
    return exp(x); 
}

template<class T>
Pow<T>::Pow(const T& v, float power) noexcept 
    : AUnaryFunction<T>{ v }, p{ power }
{
}

template<class T>
double Pow<T>::self_value(double x) const 
{ 
    return pow(x, p); 
}

template<class T>
double Pow<T>::self_derivative(double x) const 
{ 
    return p * pow(x, p-1); 
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_H
