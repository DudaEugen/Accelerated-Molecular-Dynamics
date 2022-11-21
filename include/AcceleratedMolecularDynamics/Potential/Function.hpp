#pragma once
#ifndef TAHD_BASE_FUNCTION_H
#define TAHD_BASE_FUNCTION_H

#include <functional>
#include "CalculationOfDerivatives/Functions.hpp"

namespace md
{
    class IBaseFunction
    {
    public:
        virtual std::function<double(double)> function() const = 0;
        virtual std::function<double(double)> derivative() const = 0;
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
        std::function<double(double)> function() const override
        {
            return func;
        }
        std::function<double(double)> derivative() const override
        {
            return utils::fcd::derivative(func);
        }
    };
}

#endif	//TAHD_BASE_FUNCTION_H
