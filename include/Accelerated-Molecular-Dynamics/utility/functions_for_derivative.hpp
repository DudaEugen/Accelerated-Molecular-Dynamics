#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include <cmath>

class Const
{
    const double value;
public:
    Const(const double v) noexcept;

    double get_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
};

class Variable
{
public:
    Variable() noexcept = default;

    double get_value(const double x) const noexcept;
    double compute_derivative(const double x) const noexcept;
};

template<class T>
class AFunction
{
protected:
    const T inner_function;

    AFunction(const T func) noexcept;
    virtual double self_value(const double x) const = 0;
    virtual double self_derivative(const double x) const = 0;
public:
    double get_value(const double x) const;
    double compute_derivative(const double x) const;
};

template<class T>
class Exp: public AFunction<T>
{
protected:
    double self_value(const double x) const override;
    double self_derivative(const double x) const override;
public:
    Exp(const T v) noexcept;
};

template<class T>
class Pow: public AFunction<T>
{
    const float p;
protected:
    double self_value(const double x) const override;
    double self_derivative(const double x) const override;
public:
    Pow(const T v, const float power) noexcept;
};

template<class T>
auto f_exp(const T v) noexcept { return Exp<decltype(v)>(v); }

template<class T>
auto f_pow(const T v, const float p) noexcept { return Pow<decltype(v)>(v, p); }

template<class T>
double compute_value(const T function, const double argument)
{
    return function.get_value(argument);
}

template<class T>
double compute_derivative(const T function, const double argument)
{
    return function.compute_derivative(argument);
}

template<class T>
AFunction<T>::AFunction(const T func) noexcept
    : inner_function{ func }
{
}

template<class T>
double AFunction<T>::get_value(const double x) const
{ 
    return self_value(inner_function.get_value(x)); 
}

template<class T>
double AFunction<T>::compute_derivative(const double x) const
{
    return self_derivative(inner_function.get_value(x)) * inner_function.compute_derivative(x);
}

template<class T>
Exp<T>::Exp(const T v) noexcept
    : AFunction<T>{ v }
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
    : AFunction<T>{ v }, p{ power }
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
