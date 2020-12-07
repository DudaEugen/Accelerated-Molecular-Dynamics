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
class Exp
{
    T inner_function;
public:
    Exp(T v): inner_function{ v }
    {
    }

    double get_value(double x) { return exp(inner_function.get_value(x)); }
    double compute_derivative(double x) 
    { 
        return exp(inner_function.get_value(x)) * inner_function.compute_derivative(x); 
    }
};

template<class T>
auto f_exp(T v) { return Exp<decltype(v)>(v); }

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
