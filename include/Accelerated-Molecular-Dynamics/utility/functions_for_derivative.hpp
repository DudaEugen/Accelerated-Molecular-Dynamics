#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include <cmath>

class Const
{
    const double value;
public:
    Const(const double v) noexcept;

    double compute_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
};

class Variable
{
public:
    Variable() noexcept = default;

    double compute_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
};

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
};

template<class F, class S>
class Product: public ABinaryFunction<F, S>
{
public:
    Product(const F first, const S second) noexcept;
    double compute_value(const double x) const override;
    double compute_derivative(const double x) const override;
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
};

template<class F, class S>
auto f_sum(const F first, const S second) noexcept 
{ 
    return Sum<decltype(first), decltype(second)>(first, second); 
}

template<class F, class S>
auto f_product(const F first, const S second) noexcept 
{ 
    return Product<decltype(first), decltype(second)>(first, second); 
}

template<class T>
auto f_exp(const T v) noexcept { return Exp<decltype(v)>(v); }

template<class T>
auto f_pow(const T v, const float p) noexcept { return Pow<decltype(v)>(v, p); }

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
