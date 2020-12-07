#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_H
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_H

#include <cmath>

class Const
{
    double value;
public:
    Const(double v);

    double get_value(double x);
    double compute_derivative(double x);
};

class Variable
{
public:
    Variable() = default;

    double get_value(double x);
    double compute_derivative(double x);
};

template<class T>
class AFunction
{
protected:
    T inner_function;

    AFunction(T func): inner_function{ func }
    {
    }
    virtual double self_value(double x) = 0;
    virtual double self_derivative(double x) = 0;
public:
    double get_value(double x) { return self_value(inner_function.get_value(x)); }
    double compute_derivative(double x)
    {
        return self_derivative(inner_function.get_value(x)) * inner_function.compute_derivative(x);
    }
};

template<class T>
class Exp: public AFunction<T>
{
protected:
    double self_value(double x) override { return exp(x); }
    double self_derivative(double x) override { return exp(x); }
public:
    Exp(T v): AFunction<T>{ v }
    {
    }
};

template<class T>
class Pow: public AFunction<T>
{
    float p;
protected:
    double self_value(double x) override { return pow(x, p); }
    double self_derivative(double x) override { return p * pow(x, p-1); }
public:
    Pow(T v, float power): AFunction<T>{ v }, p{ power }
    {
    }
};

template<class T>
auto f_exp(T v) { return Exp<decltype(v)>(v); }

template<class T>
auto f_pow(T v, float p) { return Pow<decltype(v)>(v, p); }

template<class T>
double compute_value(T function, double argument)
{
    return function.get_value(argument);
}

template<class T>
double compute_derivative(T function, double argument)
{
    return function.compute_derivative(argument);
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_H
