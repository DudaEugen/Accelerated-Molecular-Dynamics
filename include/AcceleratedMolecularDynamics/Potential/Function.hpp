#pragma once
#ifndef TAHD_BASE_FUNCTION_H
#define TAHD_BASE_FUNCTION_H

#include "CalculationOfDerivatives/Functions.hpp"

namespace md
{
    class IBaseFunction
    {
    public:
        virtual double function(double value) const = 0;
        virtual double derivative(double value) const = 0;
        virtual ~IBaseFunction() = 0;
    };

    template<class T, class U>
    struct Function: public IBaseFunction
    {
    private:
        U func;

    public:
        Function(T function): func{ function }
        {
        }
        Function(T function, const std::vector<double>& params): 
            func{ utils::fcd::setParameters(function, params) }
        {
        }
        double function(double value) const override
        {
            return func(value);
        }
        double derivative(double value) const override
        {
            return utils::fcd::derivative(func)(value);
        }
    };
}

#endif	//TAHD_BASE_FUNCTION_H
